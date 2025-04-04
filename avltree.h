//
// Created by yagmur on 12/28/2024.
//

#ifndef CNG213A3_AVLTREE_H
#define CNG213A3_AVLTREE_H
#define FALSE 0
#define TRUE 1

struct Date {
    int day;
    int month;
    int year;
};
struct Patient {
    char name[50];
    char surname[50];
    struct Date dob;
    float height;
    int weight;
    struct Patient *next;
};

typedef struct Node *AVLTree;
struct Node
{
    float BMI;
    struct Patient *patients;
    AVLTree left;
    AVLTree right;
    int height_of_tree;
};

//default functions from the template
AVLTree CreateTree(void);
AVLTree MakeEmptyTree(AVLTree);
AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);
int AVLTreeHeight(AVLTree);
int Max(int, int);

//modified or created functions
AVLTree loadPatients(int argc, char *argv[]);
AVLTree InsertPatient(char [],char [], int , int , int , float, int , float , AVLTree );
void DisplayPatients(AVLTree);
int infoPatient(AVLTree, float);
struct Patient *youngestPatient(AVLTree);
void printYoungestPatient(struct Patient *);
#endif //CNG213A3_AVLTREE_H
