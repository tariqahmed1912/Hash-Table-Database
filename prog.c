#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

typedef struct Node {
    struct Node *prev;
    int value;
    struct Node *next;
} node;

// 'hashtable' is an array of pointers.
node* hashtable[SIZE];

bool insertElement(int elem);
bool searchElement(int elem);
bool deleteElement(int elem);
void displayHashTable();
int hash(int elem);

int main () {
    int option, elem, flag = 0;

    for (int i=0; i < SIZE; i++){
        hashtable[i] = NULL;
    }

    printf("Welcome! Get started with hashing!\n");
    
    do {
        printf("Menu:\n1. Insert\n2. Search\n3. Delete\n4. Display\n\n");
        scanf("%d", &option);

        printf("Enter element: ");
        scanf("%d", &elem);

        bool res=false;
        switch (option)
        {
        case 1: 
            res = insertElement(elem); break;
        case 2: 
            res = searchElement(elem); break;
        case 3: 
            res = deleteElement(elem); break;
        case 4: 
            displayHashTable(); break;
        case 5: 
            printf("Quitting..\n");
            flag = 1;
            break;
        default:
            printf("Please enter valid option.\n"); break;
        }

        if (res == true) {
            printf("Successful!\n");
        } else{
            printf("Not successful..\n");
        }
    } while (flag != 1);
    
    return 0;
}

// hash function
int hash(int elem) {
    int key = elem % SIZE;
    return key;
}

// function to insert a record
bool insertElement(int elem) {
    int key = hash(elem);

    node* newNode = malloc(sizeof(node));
    newNode->value = elem;
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
    return true;        
}

// function to search for a particular record
bool searchElement(int elem) {
    int key = hash(elem);
    node* current = hashtable[key];
    if (current == NULL) {
        return false;
    }

    while (current != NULL) {
        if (current->value == elem) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// function to delete a record
bool deleteElement(int elem) {
    int key = hash(elem);
    node* current = hashtable[key];
    node* prev = NULL;
    if (current == NULL) {
        printf("Element does not exist. ");
        return false;
    }
    
    while (current != NULL && current->value != elem) {
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