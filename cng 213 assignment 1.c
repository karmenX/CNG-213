#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definiton of struct Date for the informations of birthday
struct Date {
    int day;
    int month;
    int year;
};

//definition of structure for patient informations
struct patient_list{
    char first_name[100];
    char last_name[100];
    struct Date dob;
    float height;
    float weight;
    char status[100];
    struct patient_list *next;
};

//definiton of node structure
struct listRecord{
    struct patient_list *head;
    struct patient_list *tail;
    int size;
};

struct listRecord *initialisePatients(char filename[]);
struct patient_list *createNewPatient(char *first_name, char *last_name,int day, int month, int year, float height, float weight, char *status);
void InsertNewPatient(struct listRecord *list);
struct patient_list *binarySearch(struct listRecord *list,char *firstname);
void SearchPatient(struct listRecord *list,char *firstname);
float calculateBMI(float height, float weight);
void UpdateNutritionalStatus(struct patient_list *list);
void initialiseUnhealtyPatientList(struct listRecord *list, struct listRecord *unhealty);
void printPatients(struct patient_list *list);

int main(){

    int command;
    int loop=0;
    char file_name[100];
    char firstname[100];

    //assigning healthy and unhealthy list to NULL

    struct listRecord *healty_list=(struct listRecord *)malloc(sizeof(struct listRecord));
    healty_list->head = healty_list->tail = NULL;
    healty_list->size = 0;

    struct listRecord *unhealty_list = (struct listRecord *)malloc(sizeof(struct listRecord));
    unhealty_list->head = unhealty_list->tail = NULL;
    unhealty_list->size = 0;

    printf("Enter the file name you want to work on: ");
    scanf("%s",file_name);
    healty_list=initialisePatients(file_name);//assigning healthy list to the linked list created in the function
    printf("The patients.txt file has been loaded successfully.\n");
    printf("----- MENU ----- \n");
    while(!loop){

        printf("1. Add patient  \n"
               "2. Show patients \n"
               "3. Search patient \n"
               "4. Create an unhealthy patient list  \n"
               "5. Show unhealthy patients \n"
               "6. Exit\n");

        printf("Enter your option: ");
        scanf("%d",&command);

        switch (command) {
            case 1:
                InsertNewPatient(healty_list);
                break;
            case 2:
                printPatients(healty_list->head);
                break;
            case 3:
                printf("Enter the name of the patient you want to search: ");
                scanf("%s",firstname);
                SearchPatient(healty_list,firstname);
                break;
            case 4:
                initialiseUnhealtyPatientList(healty_list,unhealty_list);
                break;
            case 5:
                printPatients(unhealty_list->head);
                break;
            case 6:
                loop=1;
                break;
            default:
                printf("Command not recognized. Try again!\n");
                break;

        }

    }
    free(healty_list);
    free(unhealty_list);

    return 0;
}

//creating a function to make it simpler by calling the function whenever we want to create a node for a new patient.
struct patient_list *createNewPatient(char *first_name, char *last_name,int day, int month, int year, float height, float weight, char *status) {

    //creating a node called newPatient and assigning the information to the corrected places.

    struct patient_list *newPatient = (struct patient_list *) malloc(sizeof(struct patient_list));
    if (newPatient == NULL) {
        printf("Error creating new patient!\n");
        exit(1);
    }
    strcpy(newPatient->first_name, first_name);
    strcpy(newPatient->last_name, last_name);
    newPatient->dob.day = day;
    newPatient->dob.month = month;
    newPatient->dob.year = year;
    newPatient->height=height;
    newPatient->weight=weight;
    strcpy(newPatient->status, status);
    newPatient->next = NULL;
    return newPatient;
}

struct listRecord *initialisePatients(char filename[]) {
    char first_name[100], last_name[100], status[100];
    int day, month, year;
    float height, weight;

    //creating and opening the stream

    FILE *stream = fopen(filename, "r");
    if (stream == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }

    //creating a temporary list to hold the data

    struct listRecord *list = (struct listRecord*) malloc(sizeof (struct listRecord));
    if(list==NULL){
        printf("Error memory allocation failed.\n");
        exit(1);
    }
    list->head=NULL;
    list->tail=NULL;
    list->size=0;

    //taking the information from the external file and putting into the linked list
    while (fscanf(stream, "%99[^;];%99[^;];%d/%d/%d;%f;%f;%99[^\n]", first_name, last_name, &day, &month, &year, &height, &weight, status) == 8) {

        //creating a node for each patient
        struct patient_list *new_patient = createNewPatient(first_name, last_name, day, month, year, height, weight, status);

        //if the list is empty or the first name comes before the names on the linked list
        if (list->head == NULL || strcmp(new_patient->first_name, list->head->first_name) < 0) {
            new_patient->next = list->head;//patient next goes to the list because it should've been placed in the beginning of the linked list
            list->head = new_patient;//assigning list pointer to the new patient, to point the head of the list(which is the added patient)
            if(list->tail==NULL)//if the tail(end) of the linked list is empty -which means the list is empty-
                list->tail=new_patient;//assign the tail to point the first node of the list
        } else {
            struct patient_list *current = list->head;

            //if the first name doesn't come before the current name, move current to current->next until we found the correct place for the name
            while (current->next != NULL && strcmp(new_patient->first_name, current->next->first_name) > 0) {
                current = current->next;
            }
            new_patient->next = current->next;//assign new node next to current->next which means we are linking the new node to the current->next
            current->next = new_patient;//linking current next to new node, therefore we successfully placed the node to the correct place
            if(new_patient->next==NULL)
                list->tail=new_patient;//assigning the end of the list to the new added node at the end of the list
        }
        list->size++;
    }
    UpdateNutritionalStatus(list);

    fclose(stream);
    return list;
}


void InsertNewPatient(struct listRecord *list) {
    char first_name[100], last_name[100];
    int day, month, year;
    float height, weight;

    //taking inputs
    printf("Enter patient's first name: ");
    scanf("%s", first_name);
    printf("Enter patient's last name: ");
    scanf("%s", last_name);
    printf("Enter patient's date of birth (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &day, &month, &year);
    printf("Enter patient's height (m): ");
    scanf("%f", &height);
    printf("Enter patient's weight (kg): ");
    scanf("%f", &weight);

    struct patient_list *new_patient = createNewPatient(first_name, last_name, day, month, year, height, weight, "NA");

    //applying the same algorithm to find the correct place for the name and place the name
    if (list->head == NULL || strcmp(new_patient->first_name, list->head->first_name) < 0) {
        new_patient->next = list->head;
        list->head = new_patient;
        if(list->tail==NULL)
            list->tail=new_patient;
    } else {
        struct patient_list *current = list->head;

        while (current->next != NULL && strcmp(new_patient->first_name, current->next->first_name) > 0) {
            current = current->next;
        }
        new_patient->next = current->next;
        current->next = new_patient;
        if(new_patient->next==NULL)
            list->tail=new_patient;
    }
    list->size++;
    UpdateNutritionalStatus(list);
}
//Since we can't apply binary search to a linked list, I created an array with the linked list information and tried to find the searched name in the list
struct patient_list *binarySearch(struct listRecord *list, char *firstname) {
    struct patient_list **array = (struct patient_list **) malloc(list->size * sizeof(struct patient_list *));
    struct patient_list *current = list->head;
    int index = 0;

    //assigning the information to the array
    while (current != NULL) {
        array[index++] = current;
        current = current->next;
    }

    //binary search algorithm
    int left = 0;
    int right = list->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(array[mid]->first_name, firstname);

        if (cmp == 0) {
            struct patient_list *found = array[mid];
            free(array);
            return found;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    free(array);
    return NULL;
}


void SearchPatient(struct listRecord *list, char *firstname) {

    //calling binary search function and assigning the information to a node called result
    struct patient_list *result = binarySearch(list, firstname);

    //printing the patient wanted
    if (result != NULL) {
        printf("Patient found: %s %s %02d/%02d/%04d %.2f %.1f %s\n",
               result->first_name, result->last_name,
               result->dob.day, result->dob.month, result->dob.year,
               result->height, result->weight, result->status);
    } else {
        printf("Patient not found.\n");
    }
}


float calculateBMI(float height, float weight){
    return weight/(height*height);
}

void UpdateNutritionalStatus(struct patient_list *list){

    float bmi;
    //comparing the bmi values and assigning true status
    while(list!=NULL){
        bmi=calculateBMI(list->height,list->weight);
        if(bmi<18.5)
            strcpy(list->status,"Underweight");
        else if(bmi<=24.9)
            strcpy(list->status,"Normal Weight");
        else if(bmi<=29.9)
            strcpy(list->status,"Pre-Obesity");
        else if(bmi<34.9)
            strcpy(list->status,"Obese Class I");
        else if(bmi<39.9)
            strcpy(list->status,"Obese Class II");
        else
            strcpy(list->status,"Obese Class III");

        list=list->next;

    }

}

void initialiseUnhealtyPatientList(struct listRecord *list,struct listRecord *unhealty) {

    //initializing the created current to point the list beginning
    struct patient_list *current = list->head;
    struct patient_list *previous = NULL;
    int count = 0;

    while (current != NULL) {
        //if the compared status shows that the patient is unhealthy
        if (strcmp(current->status, "Obese Class I") == 0 || strcmp(current->status, "Obese Class II") == 0 ||
            strcmp(current->status, "Obese Class III") == 0) {

            //creating unhealthy_patient node to hold the current patient -which we want to remove-
            struct patient_list *unhealthy_patient = current;
            if (previous == NULL)//if the patient is at the top of the list
                list->head = current->next;//assigning list head to the next node
            if (current->next == NULL) {//if the patient is at the end of the list
                list->tail = previous;//assigning list tail to hold the previous patient
                previous->next = NULL;
            }
            current = current->next;
            //adding the patient to unhealthy list
            if (unhealty->head == NULL)//if the list is empty
                unhealty->head = unhealty->tail = unhealthy_patient;//point to unhealthy_patient as first node
            else {
                unhealty->tail->next = unhealthy_patient;//add to the end of the unhealthy list
                unhealty->tail = unhealthy_patient;
            }
            unhealty->size++;
            list->size--;
            count++;
        } else {
            previous = current;
            current = current->next;

        }
    }
    printf("The number of patients removed from the patient list and moved to the unhealthy patients list is %d",count);
}

void printPatients(struct patient_list *list){

    if(list==NULL){
        printf("List is empty.\n");
    }
    else {
        printf("Patients are as follows:\n");
        while (list != NULL) {
            printf("%s %s %02d/%02d/%04d %.2f %.1f %s\n",
                   list->first_name, list->last_name,
                   list->dob.day, list->dob.month, list->dob.year,
                   list->height, list->weight, list->status);

            list = list->next;
        }
        printf("\n");
    }
}