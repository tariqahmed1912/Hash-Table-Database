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

node* insertElement();
void searchElement();
void deleteElement();
void displayHashTable();
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
        printf("Options:\n1. (I)nsert a record\n2. (S)earch for a record\n3. (D)elete a record\n4. (V)iew all records\n5. Quit\n\n");
        printf("Enter option: ");
        scanf("%c", &option);

        switch (option)
        {
        case 'I': 
            //node* = insertElement(); 
            int x = 10;
            int y = 20;
            int z = x+y;
            printf("%d", z);
            // printf("Record successfully added.");
            // printf("UserID\tSalary");
            // printf("%d\t%d", new->uid, new->salary);
            break;
        case 'S': 
            searchElement(); break;
        case 'D': 
            deleteElement(); break;
        case 'V': 
            displayHashTable(); break;
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
node* insertElement() {
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
    
    return newNode;      
}

// function to search for a particular record
void searchElement() {
    int uid;
    printf("Enter UserID: ");
    scanf("%d", &uid);
    
    int key = hash(uid);
    node* current = hashtable[key];
    if (current == NULL) {
        return false;
    }

    while (current != NULL) {
        if (current->uid == uid) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// function to delete a record
void deleteElement() {
    int uid;
    printf("Enter UserID: ");
    scanf("%d", &uid);
    
    int key = hash(uid);
    node* current = hashtable[key];
    node* prev = NULL;
    if (current == NULL) {
        printf("Element does not exist. ");
        return false;
    }
    
    while (current != NULL && current->uid != uid) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Element not found.");
        return false;
    }

    prev->next = current->next;
    current->next->prev = current->prev;
    
    return false;
}

// function to display database (all records) 
void displayHashTable() {
    printf("Index\tValue\n");
    printf("-----\t-----\n");
    for (int i=0; i < SIZE; i++) {
        printf("%d\t", i);
        if ( hashtable[i] != 0 ) {
            node* current = hashtable[i];
            
            while (current->next != NULL) {
                printf("%d (%d)--->", current->value, current);
                current = current->next; 
            }
            printf("%d (%d)\n", current->value, current);
        }
        else {
            printf("%d\n", hashtable[i]);
        }
    }
}