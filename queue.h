//
// Created by yagmu on 12/3/2024.
//

#ifndef STUDY_QUEUE_H
#define STUDY_QUEUE_H

//Minimum queue size - minimum number of elements that
//can be stored in a queue
#define MIN_QUEUE_SIZE 5
//Maximum queue size - maximum number of elements that
//can be stored in a queue
#define MAX_QUEUE_SIZE 100

#define FALSE 0
#define TRUE 1


//Queue record that holds the following data:
//capacity: the capacity of the queue,
//front: index of the front element
//rear: index of the rear element
//size: size of the queue
//array: the array to hold the data in the stack
struct QueueRecord
{
    int capacity;
    int front;
    int rear;
    int size;
    int *array;
};

typedef struct QueueRecord *Queue;

//Function signatures
Queue CreateQueue(int);
void MakeEmptyQueue(Queue);
int Succ(int, Queue);
void Enqueue(int, Queue);
int Dequeue(Queue);
int FrontOfQueue(Queue);
int RearOfQueue(Queue);
int IsFullQueue(Queue);
int IsEmptyQueue(Queue);
void DisplayQueue(Queue);

#endif //STUDY_QUEUE_H
