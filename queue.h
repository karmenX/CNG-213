//
// Created by yagmu on 12/8/2024.
//

#ifndef CNG213A2_QUEUE_H
#define CNG213A2_QUEUE_H

// Definition of a single packet
struct Packet {
    int arrival_time;
    int transmission_time;
    int transmission_start_time;
    int ID;
    int priority;
    struct Packet *next;
};

// Definition of queue
struct Queue {
    struct Packet *front;
    struct Packet *rear;
    int size;
};

// Definition of a linked list for packets
struct List_of_packets {
    struct Packet *Node;
    struct List_of_packets *next;
};

//definition of functions
typedef struct List_of_packets *List;
int parseInput(int argc, char *argv[], int *noOfPackets, int *noOfSwitchers, int *maxArrivalTime, int *maxTransmissionTime);
List createPacketsList(int , int , int );
struct Queue *initialiseSimulator(int , int **);
void newPacket(struct Queue *, List );
void transmitPacket(struct Queue * , int *, int ,int *, int *);
void reportStatistics(struct Queue *, int *, int ,int, int );


#endif //CNG213A2_QUEUE_H