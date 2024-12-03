#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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


