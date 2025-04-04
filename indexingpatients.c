//Yağmur Can 2637536

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

//default functions from the template
AVLTree CreateTree(void)
{
    return NULL;
}

AVLTree MakeEmptyTree(AVLTree t)
{
    if (t != NULL)
    {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

int AVLTreeHeight(AVLTree t)
{
    if (t == NULL)
        return -1;
    else
        return t->height_of_tree;
}

AVLTree SingleRotateWithLeft(AVLTree k1) {
    AVLTree k2;
    k2=k1->right;
    k1->right=k2->left;
    k2->left=k1;

    //update height
    k1->height_of_tree= Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right))+1;
    k2->height_of_tree= Max(AVLTreeHeight(k2->right), k1->height_of_tree)+1;
    //you can write it as K2->height=Max(AVLTreeHeight(k2->right),AVLTreeHeight(k2->left))+1

    return k2;//new root
}

AVLTree SingleRotateWithRight(AVLTree k2) {
    AVLTree k1;
    k1=k2->left;//assigning k1 to the root's left subtree, so that we can work with it
    k2->left=k1->right;//k1->right is NULL, and with this line we make k2's two subtrees NULL, so it became a single node
    k1->right=k2;//k1's right was NULL, then we added k2 which is a single node now with the biggest value of all three

    //update height
    k2->height_of_tree= Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right))+1;
    k1->height_of_tree= Max(AVLTreeHeight(k1->left), k2->height_of_tree)+1;

    return k1; //new root
}

AVLTree DoubleRotateWithLeft(AVLTree k3)
{
    AVLTree k1;
    k1=k3->left;
    k3->left=SingleRotateWithLeft(k1);

    return SingleRotateWithRight(k3);
}

AVLTree DoubleRotateWithRight(AVLTree k3)
{
    AVLTree k1;
    k1=k3->right;
    k3->right=SingleRotateWithRight(k1);

    return SingleRotateWithLeft(k3);
}

int Max(int x, int y)
{
    if (x >= y)
        return x;
    else
        return y;
}

//modified functions
int main(int argc, char *argv[])
{
    AVLTree myTree;
    int exit,x;
    char command;
    float bmi;

    exit = FALSE;
    myTree= loadPatients(argc,argv);
    printf("Welcome to Patient Indexing!!!\n");
    while (!exit)
    {
        fflush(stdin);
        printf("-----------Menu---------\n");
        printf("(1) Display the full index of patients\n");
        printf("(2)Display the details of the patients\n");
        printf("(3)Display the youngest patient\n");
        printf("(4)Exit\n");
        printf("Enter your option: ");
        scanf("%c", &command);
        fflush(stdin);

        switch (command)
        {
            case '1':
                DisplayPatients(myTree);
                break;
            case '2':
                do {
                    printf("Enter patient's BMI:");
                    scanf("%f", &bmi);
                    x=infoPatient(myTree, bmi);
                }while(x==0);
                break;
            case '3':
                printYoungestPatient(youngestPatient(myTree));
                break;
            case '4':
                exit = TRUE;
                break;
            default:
                printf("Command not recognized\n");
                break;
        }
    }
    printf("\n");
    system("PAUSE");
    return 0;
}

AVLTree loadPatients(int argc, char *argv[]){

    if (argc < 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        exit(1);
    }

    FILE *stream= fopen(argv[1],"r");
    if(stream==NULL){
        printf("Error opening file %s\n",argv[1]);
        exit(1);
    }

    AVLTree tree=CreateTree();
    int day,month,year, weight;
    char name[50],surname[50];
    float height, bmi;
    while (fscanf(stream, "%49[^;];%49[^;];%d/%d/%d;%f;%d;%f\n", name, surname, &day, &month, &year, &height, &weight, &bmi) == 8) {
        tree=InsertPatient(name,surname,day,month,year,height,weight,bmi,tree);

    }
    fclose(stream);
    return tree;
}

AVLTree InsertPatient(char name[], char surname[], int day, int month, int year, float height, int weight, float bmi, AVLTree t) {

    //if tree is empty
    if (t == NULL)
    {
        /*Create and return a one-node tree */
        t = malloc(sizeof(struct Node));
        if (t == NULL)
            printf("Out of memory space!!!\n");
        else
        {
            //create a new patient node to insert
            struct Patient *newPatient= malloc(sizeof (struct Patient));
            if(newPatient==NULL){
                printf("Error allocating memory for new patient.\n");
                exit(1);
            }
            strcpy(newPatient->name,name);
            strcpy(newPatient->surname,surname);
            newPatient->dob.day=day;
            newPatient->dob.month=month;
            newPatient->dob.year=year;
            newPatient->height=height;
            newPatient->weight=weight;
            newPatient->next=NULL;
            t->BMI=bmi;
            t->height_of_tree = 0;
            t->left = t->right = NULL;
            t->patients=newPatient;//insert new patient to the tree
        }
    }

        //if the bmi is less than the node bmi, insert to left side
    else if (bmi<t->BMI)
    {
        t->left = InsertPatient( name, surname, day, month, year,  height, weight, bmi, t->left);

        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2) {
            if (bmi < t->left->BMI)
                t = SingleRotateWithRight(t);
            else
                t = DoubleRotateWithLeft(t);
        }
        t->height_of_tree = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
    }
        //if the bmi is greater than the node bmi, insert to right side
    else if (bmi > t->BMI)
    {
        t->right = InsertPatient( name, surname, day, month, year,  height, weight, bmi, t->right);
        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2) {
            if (bmi> t->right->BMI)
                t = SingleRotateWithLeft(t);
            else
                t = DoubleRotateWithRight(t);
        }
        t->height_of_tree = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
    }
        //BMI is already in the tree, insert to the existing node with the same bmi
    else{
        struct Patient *newPatient= malloc(sizeof (struct Patient));
        if(newPatient==NULL){
            printf("Error allocating memory for new patient.\n");
            exit(1);
        }
        strcpy(newPatient->name,name);
        strcpy(newPatient->surname,surname);
        newPatient->dob.day=day;
        newPatient->dob.month=month;
        newPatient->dob.year=year;
        newPatient->height=height;
        newPatient->weight=weight;
        newPatient->next=t->patients;
        t->patients=newPatient;
    }
    return t;
}

void DisplayPatients(AVLTree t) {

    if (t != NULL)
    {
        DisplayPatients(t->left);

        //traverse the list of patients and print
        struct Patient *tmp=t->patients;
        while(tmp!=NULL) {
            printf("%s;%s;%d/%d/%d;%.2f;%d;%.1f\n",
                   tmp->name, tmp->surname, tmp->dob.day, tmp->dob.month,
                   tmp->dob.year, tmp->height, tmp->weight, t->BMI);
            tmp=tmp->next;
        }
        DisplayPatients(t->right);
    }
}

int infoPatient(AVLTree t, float bmi){

    if(t==NULL){//executed just once therefore the time complexity of this statement is O(1)
        printf("There is not an available patient who has a BMI of %.1f\n",bmi);
        return 0;
    }
    //Traversing the tree to find the bmi value with binary search
    //The complexity of binary search is O(logN) with N being the number of Nodes in the AVL tree
    if(bmi<t->BMI){
        return infoPatient(t->left,bmi);
    }
    else if(bmi>t->BMI){
        return infoPatient(t->right,bmi);
    }
    //binary search ends here. we found the node with the wanted bmi value
    else {
        //we traverse the linked list structure to print the patients
        struct Patient *tmp = t->patients;//assigning a temporary node
        while (tmp != NULL) {
            //iterating the list until we reach the end of it with linear search
            //the time complexity of a linear search is O(N) with N being the number of patients in this case
            printf("%s;%s;%d/%d/%d;%.2f;%d;%.1f\n",
                       tmp->name, tmp->surname, tmp->dob.day, tmp->dob.month,
                       tmp->dob.year, tmp->height, tmp->weight, t->BMI);
                tmp = tmp->next;
        }
        return 1;
    }
    //therefore as total the time complexity is O(logN)+O(N), the N values represents different things, so instead we can write O(logN+K)
    //I don't think there are any further methods to improve this function because we created the AVL tree as MIN based,
    //means actually the first node(root) is the middle of the bmi values which makes the binary search effective
}

struct Patient *youngestPatient(AVLTree t){

    //the calculation logic:
    //adding the days, months(30 days based) and years(365 days based) will give us how many days after the year 0-which will be our base scenario-
    //If the number is bigger then it means the person has born later, which makes him/her younger

    int total_days;
    int max_total_days=0;
    struct Patient *youngest=NULL;

    if(t!=NULL) {
        //iterating the list until we reach the end of it with linear search
        //the time complexity of a linear search is O(N) with N being the number of patients in this case
        struct Patient *tmp = t->patients;
        while (tmp != NULL) {
            total_days = tmp->dob.day + (tmp->dob.month * 30) + (tmp->dob.year * 365);
            //comparing the initial total days with the current patients total days
            if (total_days > max_total_days) {
                max_total_days = total_days;
                youngest = tmp;
            }
            tmp = tmp->next;
        }
        //the function call itself to move to left and right subtrees
        //since the function visits all the nodes, the time complexity will be O(N), N representing the number of nodes
        struct Patient *youngest_left = youngestPatient(t->left);
        if (youngest_left != NULL) {
            int days = youngest_left->dob.day + (youngest_left->dob.month * 30) + (youngest_left->dob.year * 365);
            if (days > max_total_days) {
                max_total_days = days;
                youngest = youngest_left;
            }
        }
        struct Patient *youngest_right = youngestPatient(t->right);
        if (youngest_right != NULL) {
            int days = youngest_right->dob.day + (youngest_right->dob.month * 30) + (youngest_right->dob.year * 365);
            if (days > max_total_days) {
                max_total_days = days;
                youngest = youngest_right;
            }
        }
    }
    //the total time complexity will be then O(N)+O(N), but since N values represents different things,so we can write O(N+K),
    // with N:number of nodes, K:number of patients in the nodes
    //I think if we implemented another value as age for every patient and created the AVL tree as MIN HEAP ,
    // the root will be the youngest patient therefore the complexity will be O(1) by just reaching to the root.
    //This kind of improvement could be done, yet the assignment does not require

   return youngest;
}

//function to print the youngest patient
void printYoungestPatient(struct Patient *youngest) {
    if (youngest != NULL) {
        printf("%s %s is the youngest patient.\n",youngest->name, youngest->surname);
    }
}