#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*Creates a queue*/
Queue CreateQueue(int maxElements)
{
    struct QueueRecord *queue;
    if(maxElements<MIN_QUEUE_SIZE){
        printf("Queue size is too small.\n");
        exit(1);
    }

    queue= malloc(sizeof (struct QueueRecord));
    if(queue==NULL){
        printf("Error allocating queue.\n");
        exit(1);
    }

    queue->array= malloc(sizeof (int )*maxElements);
    if(queue->array==NULL){
        printf("Error allocating array.\n");
        exit(1);
    }
    queue->capacity=maxElements;
    MakeEmptyQueue(queue);
    return queue;
}

/*Makes an empty queue*/
void MakeEmptyQueue(Queue q)
{
    q->size=0;
    q->front=1;
    q->rear=0;
}

/*Checks if a queue is empty*/
int IsEmptyQueue(Queue q)
{
    if(q->size==0)
        return 1;
    else
        return 0;
}


/*Checks if a queue is full*/
int IsFullQueue(Queue q)
{
    if(q->size==q->capacity)
        return 1;
    else
        return 0;
}

/*Moves the given value by one, if it is the end of the array, it makes the index 0*/
int Succ(int val, Queue q)
{
    val++;
    if(val==q->capacity){
        val=0;
    }
    return val;
}

/*Adds a new value to the rear of the queue*/
void Enqueue(int x, Queue q)
{
    if(IsFullQueue(q))
        printf("Queue is full.\n");
    else
        q->size++;
    q->rear=Succ(q->rear,q);
    q->array[q->rear]=x;

}

/*Removes a value from the front of the queue*/
int Dequeue(Queue q)
{
    int val;
    if(IsEmptyQueue(q))
        printf("Queue is empty.\n");
    else{
        val=q->array[q->front];
        q->size--;
        q->front= Succ(q->front,q);
        return val;
    }

}

/*Gives the front element in the queue*/
int FrontOfQueue(Queue q)
{
    return q->array[q->front];
}

/*Gives the rear element in the queue*/
int RearOfQueue(Queue q)
{
    return q->array[q->rear];
}

/*Displays the content of the queue*/
void DisplayQueue(Queue q)
{
    int i, pos;

    printf("Front: %d\t",q->front);
    printf("Rear: %d\n",q->rear);
    pos=q->front;
    printf("Queue content:\n");

    for (i=0; i<q->size; i++)
    {
        printf("\t--> %d\n", q->array[pos]);
        pos = Succ(pos, q);
    }
}

