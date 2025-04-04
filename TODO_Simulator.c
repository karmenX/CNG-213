//Yağmur Can
//2637536

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

//function to create a linked list containing packets
List createPacketsList(int packets, int arrival, int transmission){

    //creates a list and temporary to work with
    List list= NULL;
    List tmp=NULL;
    int arrival_time;

    //as the number of packets the user enters
    for(int count=0;count<packets;count++) {

        List new_packet= malloc(sizeof (struct List_of_packets));//creates a pointer to the packets
        new_packet->Node= malloc(sizeof (struct Packet));//creates a packet

        //assigns the values to the packet
        arrival_time=rand()%arrival+1;
        new_packet->Node->arrival_time = arrival_time;
        new_packet->Node->transmission_time = rand()%transmission +1;
        new_packet->Node->transmission_start_time = 0;
        new_packet->Node->ID = 0;
        new_packet->Node->priority=rand()%4 +1;
        new_packet->next=NULL;

        //adding the first packet to the empty list
        if(list==NULL){
            list=new_packet;
        }
        else {
            tmp = list;//assigns list to temporary
            List prev = NULL;
            //we traverse the list to find the correct position
            while (tmp != NULL && tmp->Node->arrival_time < new_packet->Node->arrival_time) {
                prev = tmp;
                tmp = tmp->next;
            }
            //we found the correct position to put the packets based on their arrival times
            if (prev == NULL) {
                new_packet->next = list;
                list = new_packet;
            } else {
                prev->next = new_packet;
                new_packet->next = tmp;
            }
        }
    }
    return list;
}

void DisplayQueue(struct Queue *q){

    struct Packet *pos;

    pos=q->front;
    printf("Queue content:\n");

    while (pos != NULL)
    {
        printf("--> priority: %d\t a_time: %d\t t_time: %d \t ID: %d  \n", pos->priority,pos->arrival_time,pos->transmission_time,pos->ID);
        pos = pos->next;
    }
}

struct Queue *initialiseSimulator(int noOfSwitchers, int **availability0fSwitchers){

    //allocates a queue
    struct Queue *queue= malloc(sizeof (struct Queue));
    if(queue==NULL){
        printf("Out of memory. Can not create queue.");
        exit(1);
    }

    //by assigning size, front and rear we created an empty queue
    queue->size=0;
    queue->front=NULL;
    queue->rear=NULL;

    //we allocate array as many as the swithcer number
    *availability0fSwitchers=  malloc(sizeof (int)*noOfSwitchers);
    if(*availability0fSwitchers==NULL){
        printf("Error creating array for the switchers.");
        free(queue);
        exit(1);
    }
    //we assign the availability of the arrays to 1
    for(int i=0;i<noOfSwitchers;i++){
        (*availability0fSwitchers)[i]=1;
    }

    return queue;
}

void newPacket(struct Queue *queue, List list) {

    //assigning a temporary list
    List temp_list = list;

    //while the temporary list is not empty(list is not empty)
    while (temp_list != NULL) {
        //assigns first node to tmp
        struct Packet *tmp = temp_list->Node;

        //if queue is empty we add the packet as first element
        if (queue->front == NULL) {
            tmp->next = NULL;
            queue->front = tmp;
            queue->rear = tmp;
        } else {
            struct Packet *current = queue->front;
            struct Packet *prev = NULL;

            //traverses list to find the correct position based on their priority levels
            while (current != NULL && current->priority >= tmp->priority) {
                prev = current;
                current = current->next;
            }
            //places the packets to the correct places
            if (prev == NULL) {//there is no higher priority
                tmp->next = queue->front;
                queue->front = tmp;
                //since we add it to the beginning we don't update the rear
            } else {
                prev->next = tmp;
                tmp->next = current;
            }

            if (current == NULL) {
                queue->rear = tmp;//if we add it to the end of the queue we update the rear to point the last element
            }
        }
        queue->size++;
        temp_list = temp_list->next;
    }
}

void transmitPacket(struct Queue * queue, int *availabilityOfSwitchers, int no0fSwitchers,int *clock,int *total_waiting_time){

    if(queue==NULL){
        printf("There is no packet to transmit.\n");
        return ;
    }

    int switcher_in_usage;
    for(int i=1;i<no0fSwitchers+1;i++){

        if(availabilityOfSwitchers[i]==1&&queue->front!=NULL){//if the switcher is available and queue is not empty
            struct Packet *transmit=queue->front;//assign first element of the queue to the transmit node

            //calculates the waiting time for each packet by substituting the arrival time from current time
            int waitingTime = *clock - transmit->arrival_time;
            if(waitingTime<0)//if the waiting time is calculated as negative it changes the sign
                waitingTime=(-1)*waitingTime;

            (*total_waiting_time)+=waitingTime;//adds each packets waiting time to find the total waiting time

            transmit->transmission_start_time=*clock;//assigns the start time as the clock(current time)
            switcher_in_usage=i;//holds the switcher number which is currently in use

            transmit->ID=i;//assigns the ID of the packet to the switcher number in which the packet is being transmitted

            *clock+= transmit->transmission_time;//adds the packet transmission time to current time

            queue->front=queue->front->next;//moves to the next element
            if(queue->front==NULL){
                queue->rear=NULL;
            }
            queue->size--;

            availabilityOfSwitchers[i]=0;
        }

    }

}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int noOfPackets, noOfSwitchers, maxArrivalTime, maxTransmissionTime;

    if(parseInput(argc, argv, &noOfPackets, &noOfSwitchers, &maxArrivalTime, &maxTransmissionTime)!=0){
        return -1;
    }

    int clock=0;
    int waiting_time=0;
    int *availabilityOfSwitchers = NULL;

    List mylist=NULL;
    struct Queue *myQueue=NULL;

    mylist=createPacketsList(noOfPackets,maxArrivalTime,maxTransmissionTime);


    myQueue= initialiseSimulator(noOfSwitchers,&availabilityOfSwitchers);
    newPacket(myQueue,mylist);

    for(int i=0;i<noOfSwitchers;i++)
        printf("Availability is: %d \n",availabilityOfSwitchers[i]);


    DisplayQueue(myQueue);
    transmitPacket(myQueue,availabilityOfSwitchers,noOfSwitchers,&clock,&waiting_time);
    reportStatistics(myQueue,&clock,waiting_time,noOfSwitchers,noOfPackets);

    return 0;
}


int parseInput(int argc, char *argv[], int *noOfPackets, int *noOfSwitchers, int *maxArrivalTime, int *maxTransmissionTime){

    if(argc!=5) {
        printf("Please enter correct number of input.\n");
        return -1;
    }
    *noOfPackets = atoi(argv[1]);
    *noOfSwitchers = atoi(argv[2]);
    *maxArrivalTime = atoi(argv[3]);
    *maxTransmissionTime = atoi(argv[4]);

    return 0;
}
void reportStatistics(struct Queue *q, int *clock, int waiting_time,int switchers, int packets){

    printf("The number of switchers is: %d\n"
           "The number of packets: %d\n", switchers, packets);

    printf("The total completion time is: %d \n",*clock);
    printf("Average waiting time in queue is: %d\n",waiting_time/packets);
    int avg,total_transmission;
    struct Queue *tmp=q->front;
    while(tmp!=NULL){
        total_transmission+=tmp->front->transmission_time;
        tmp->front=tmp->front->next;
    }
    avg=(total_transmission+waiting_time)/packets;
    printf("Average transmission time per packet is: %d",avg);


}