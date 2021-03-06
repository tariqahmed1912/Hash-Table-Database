#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10

typedef struct Node {
    struct Node *prev;
    int uid; 
    int salary;
    struct Node *next;
} node;

// 'hashtable' is an array of pointers.
node* hashtable[SIZE];

void insertRecord();
void searchRecord();
void deleteRecord();
void viewAll();
void viewHashTable();
int hash(int uid);

int main () {
    int elem, flag = 0;
    char option;

    for (int i=0; i < SIZE; i++){
        hashtable[i] = NULL;
    }

    printf("\t\tUser Management System\n");
    printf("\t\t-----------------------\n");
    
    do {
        printf("\n------------------------------------------------\n");
        printf("\nOptions:\n1. (I)nsert a record\n2. (S)earch for a record\n3. (D)elete a record\n4. (V)iew all records\n5. View (H)ash Table\n6. Quit\n\n");
        printf("Enter option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case 'I': 
            insertRecord(); break;
        case 'S': 
            searchRecord(); break;
        case 'D': 
            deleteRecord(); break;
        case 'V': 
            viewAll(); break;
        case 'H':
            viewHashTable(); break;
        case 'Q': 
            printf("Quitting..\n");
            flag = 1;
            break;
        default:
            printf("Please enter valid option.\n"); break;
        }
    } while (flag != 1);
    
    return 0;
}


// hash function
int hash(int uid) {
    int key = uid % SIZE;
    return key;
}


// function to insert a record
void insertRecord() {
    int uid, salary;
    //char name[30];

    printf("Enter UserID: "); scanf("%d", &uid);
    //printf("Enter Name: "); scanf("%[^\n]s", name);
    printf("Enter Salary: "); scanf("%d", &salary);
    int key = hash(uid);

    node* newNode = malloc(sizeof(node));
    newNode->uid = uid;
    //strcpy(newNode->name, name);
    newNode->salary = salary;
    newNode->next = NULL;

    node* current = hashtable[key];
    if ( current == NULL ) {
        hashtable[key] = newNode;
        newNode->prev = hashtable[key];
    } else {
        while (current->next != NULL) {
            current = current->next; 
        }
        current->next = newNode;
        newNode->prev = current;
    }
    
    printf("Record inserted successfully!\n");    
}


// function to search for a particular record
void searchRecord() {
    int uid, flag = 0;
    printf("Enter UserID: ");
    scanf("%d", &uid);
    
    int key = hash(uid);
    node* current = hashtable[key];
    
    while (current != NULL) {
        if (current->uid == uid) {
            flag = 1;
            break;
        }
        current = current->next;
    }
    
    if (flag == 0) {
        printf("Record not found.\n");
    } else {
        printf("Record found.\n");
        printf("UserID\tName\n");
        printf("------\t----\n");
        printf("%d\t%d\n", current->uid, current->salary);
    }
}


// function to delete a record
void deleteRecord() {
    int uid, flag = 0;
    printf("Enter UserID: ");
    scanf("%d", &uid);
    
    int key = hash(uid);
    node* current = hashtable[key];
    node* prev = NULL;
    if (current != NULL) {
        while (current != NULL && current->uid != uid) {
            prev = current;
            current = current->next;
        }

        // prev = NULL indicates that the first item in the list is being deleted.
        // If there is only one element in the list, make current a Null pointer. 
        if (prev == NULL) {
            hashtable[key] = current->next;
            if (current->next != NULL) {
                current->next->prev = hashtable[key];
            }
            free(current);
            current = NULL;
            flag = 1;
        } 

        // Enter this condition only if True when record matches.
        if (current != NULL) {
            prev->next = current->next;
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } 
            free(current);
            flag = 1;
        }
    }

    if (flag == 0) {
        printf("Record not found.\n");
    } else {
        printf("Record deleted successfully.\n");
    }
    
}

// function to display hashtable 
void viewHashTable() {
    printf("\nIndex\tValue\n");
    printf("-----\t-----\n");
    for (int i=0; i < SIZE; i++) {
        printf("%d\t", i);
        if ( hashtable[i] != 0 ) {
            node* current = hashtable[i];
            
            while (current->next != NULL) {
                printf("%d---> ", current->uid);
                current = current->next; 
            }
            printf("%d \n", current->uid);
        }
        else {
            printf("-\n");
        }
    }
}


// function to display database (all records) 
void viewAll() {
    printf("S.No.\tUserID\tSalary\n");
    printf("-----\t------\t------\n");
    int j=0;
    for (int i=0; i < SIZE; i++) {
        if (hashtable[i] == NULL) continue;
        node* tmp = hashtable[i];

        do { 
            ++j;
            printf("%d\t%d\t%d\n", j, tmp->uid, tmp->salary);
            tmp = tmp->next;
        } while (tmp != NULL);
    }
}