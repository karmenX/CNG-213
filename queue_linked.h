//
// Created by yagmu on 12/6/2024.
//

#ifndef STUDY_QUEUE_LINKED_H
#define STUDY_QUEUE_LINKED_H

#define FALSE 0
#define TRUE 1
/*A Node declaration to store a value and a link*/
struct Node
{
    int val;
    struct Node *next;
};

/*Queue Record that will store the following:
size: total number of elements stored in the list
front: it shows the front node of the queue (front of the queue)
rear: it shows the rare node of the queue (rear of the queue)*/
struct QueueRecord
{
    struct Node *front;   /* pointer to front of queue */
    struct Node *rear;    /* pointer to rear of queue */
    int size;             /* number of items in queue */
};
typedef struct QueueRecord *Queue;

Queue CreateQueue();
void MakeEmptyQueue(Queue);
int QueueSize(Queue);
void Enqueue(int, Queue);
int Dequeue(Queue);
int FrontOfQueue(Queue);
int RearOfQueue(Queue);
int IsEmptyQueue(Queue);
void DisplayQueue(Queue);
#endif //STUDY_QUEUE_LINKED_H
