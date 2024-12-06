#include <stdio.h>
#include <stdlib.h>
#include "queue_linked.h"


/*This function initialises the queue*/
Queue CreateQueue()
{
    struct QueueRecord *queue;
    queue=malloc(sizeof (struct QueueRecord));
    if(queue==NULL){
        printf("Out of memory space.\n");
        exit(1);
    }
    MakeEmptyQueue(queue);
    return queue;
}

/*This function sets the queue size to 0, and creates a dummy element
and sets the front and rear point to this dummy element*/
void MakeEmptyQueue(Queue q)
{
    struct Node *newnode= malloc(sizeof (struct Node));
    q->size=0;
    q->front=newnode;
    if(q->front==NULL){
        printf("Error. q->front could not created.\n");
        exit(1);
    }
    q->front->next=NULL;
    q->rear=q->front;

}

/*Shows if the queue is empty*/
int IsEmptyQueue(Queue q)
{
    if(q->size==0)
        return 1;
    else
        return 0;
}

/*Returns the queue size*/
int QueueSize(Queue q)
{
    return q->size;
}

/*Enqueue - Adds a new element to the queue, simly creates a node and
adds it to the rear of the queue*/
void Enqueue(int x, Queue q)
{
    struct Node *new= malloc(sizeof (struct Node));
    new->val=x;
    new->next=NULL;
    q->rear->next=new;
    q->rear=new;
    q->size++;
}

/*Dequeue - Removes a node from the queue, basically removes a node from
the front of the queue*/
int Dequeue(Queue q)
{
    if(IsEmptyQueue(q)){
        printf("Queue is empty.\n");
        return -1;
    }
    struct Node *remove;
    int waiting;
    remove=q->front->next;
    waiting=q->front->next->val;
    q->front->next=remove->next;
    if(remove->next==NULL)
        q->rear=q->front;
    free(remove);
    q->size--;
    return waiting;


}

/*Returns the value stored in the front of the queue*/
int FrontOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->front->next->val;
    else
    {
        printf("The queue is empty\n");
        return -1;
    }
}

/*Returns the value stored in the rear of the queue*/
int RearOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->rear->val;
    else
    {
        printf("The queue is empty\n");
        return -1;
    }
}

/*Displays the content of the queue*/
void DisplayQueue(Queue q)
{
    if(IsEmptyQueue(q)){
        printf("Queue is empty.\n");
    }
    struct Node *print;

    print = q->front->next;

    while (print != NULL)
    {
        printf("--> %d  ", print->val);
        print = print->next;
    }
    printf("\n");
}


