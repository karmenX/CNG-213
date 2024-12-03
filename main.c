#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    int queueSize;
    Queue myQueue;
    int exit, val;
    char command;

    printf("Enter queue size: ");
    scanf("%d", &queueSize);
    myQueue = CreateQueue(queueSize);

    exit = FALSE;

    while (!exit)
    {
        fflush(stdin);
        printf("Enter command "
               "i)nitialize "
               "e)nqueue "
               "d)equeue "
               "f)ront queue "
               "r)ear queue "
               "t)erminate: ");

        scanf("%c", &command);
        fflush(stdin);

        switch(command)
        {
            case 'i':
                MakeEmptyQueue(myQueue);
                break;
            case 'e':
                printf("enter value: ");
                scanf("%d", &val);
                Enqueue(val, myQueue);
                break;
            case 'd':
                val = Dequeue(myQueue);
                break;
            case 'f':
                val = FrontOfQueue(myQueue);
                if (val != -1)
                    printf("front element is %d\n", val);
                break;
            case 'r':
                val = RearOfQueue(myQueue);
                if (val != -1)
                    printf("rear element is %d\n", val);
                break;
            case 't':
                exit = TRUE;
                break;

            default:
                printf("command not recognized\n");
                break;
        }
        DisplayQueue(myQueue);

    }

    printf("\n\n");
    system("PAUSE");
    return 0;
}


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