/*
Author: Austin Bevacqua
Student ID: 20162896
File: Linkedlist.c
Purpose: A file which defines functions related to the linked list struct
Last Modified: 23/10/20
*/

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/**********************
Function Create Linked List
Purpose: Mallocs a new linked list struct and sets default variables
Date: 14/10/20
Author: Austin Bevacqua
**********************/
LinkedList* createLinkedList() {
    LinkedList* list;
    list = (LinkedList*)malloc(sizeof(LinkedList));
    /* Default values for struct variables are set as NULL */
    list->head = NULL;
    list->tail = NULL;
    return list; /* The newly malloced linked list struct is returned */
}


/**********************
Function Find At
Purpose: Indexes a linked list at location (index)
Date: 14/10/20
Author: Austin Bevacqua
**********************/
void* findAt(LinkedList* list, int index) {
    LinkedListNode* currNode;
    void* data;
    int i;

    currNode = list->head;
    /* The for loop continues until we reach the indexed location OR a null node */
    for(i = 0; (i < index) && (currNode != NULL); i++) {
        data = currNode->data;
        currNode = currNode->next;
    }
    /* If a null node is reached, the index is out of range of the linked list
    Likewise, if the index is a negative number, it is out of range */
    if((currNode == NULL) || (index < 0)) {
        /* We notify the user that the imported index is out of range */
        printf("Error: index not in range of linked list");
        data = NULL;
    }

    /* If no other errors have occured, we return the DATA of the indexed location */ 
    else {
        data = currNode->data;
    }

    return data;
}
        

/**********************
Function Insert Start
Purpose: Inserts an eleement at the FIRST INDEX of a linked list
Date: 14/10/20
Author: Austin Bevacqua
**********************/
void insertStart(LinkedList* list, void* entry) {
    LinkedListNode *newNode;
    newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    /* First, the values of the new node are initalised */
    newNode->data = entry;
    newNode->next = list->head; /*The node currently at HEAD */
    newNode->prev = NULL; /*The pointer of HEAD*/
    
    /* If the head node is currenly NULL / the list is empty */
    if (list->head == NULL) {
        /* If the list is empty, the head and tail are set to be the new node */
        list->head = newNode;
        list->tail = newNode;
    }
    /* If the list is not empty, we adjust the links between nodes accordingly */
    else {
        /* The current head node is set as second node
            The new node is set as the new head, with the old head as the NEXT value */
        list->head->prev = newNode; 
        newNode->next = list->head;
        list->head = newNode;
    }
    list->count += 1; /* The node counter is increased by one */
}

/**********************
Function Insert Last
Purpose: Inserts a value at last value of the linked list
Date: 14/10/20
Author: Austin Bevacqua
**********************/
void insertLast(LinkedList* list, void* entry) {
    LinkedListNode *newNode;
    newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    newNode->data = entry;
    newNode->next = NULL;
    newNode->prev = list->tail;

    /* If the head node is currenly NULL / the list is empty */
    if (list->head == NULL) {
        /* If the list is empty, the head and tail are set to be the new node */
        list->head = newNode;
        list->tail = newNode;
    }
    else {
        list->tail->next = newNode;
        list->tail = newNode; 
    }
    list->count += 1;
}

/**********************
Function Remove Start
Purpose: Removes and returns the first value of the linked list
Date: 14/10/20
Author: Austin Bevacqua
**********************/
void* removeStart(LinkedList* list) {
    LinkedListNode* temp;
    char* data;

    temp = list->head;
    /* If the head node of the linked list is null, the list is empty
        We cannot remvve any elements as no elements exist */
    if(list->head != NULL) {
        /* We set the new head to be the next (2nd) element */
        list->head = list->head->next;
        /* If the new head is NULL, the list only contained one element, 
            therefore, we have just made the list empty. 
            We then set the tail (last element) to null */
        if(list->head == NULL) {
            list->tail = NULL;
        }
        else {
            list->head->prev = NULL;
        }
        list->count -= 1; /*We reduce the count of the linked list by 1, as we are removing one entry. */
        data = temp->data; /*The data stord in the node is stored and returned. */
        free(temp); /*We FREE the List Node, as it will no longer be accessed */
    }
    else {
        data = NULL;
        printf("FAILURE: Linked list is currently empty");
    }
    return data;
}

/**********************
Function Remove Last
Purpose: Removes and returns the last value of the linked list
Date: 14/10/20
Author: Austin Bevacqua
**********************/
void* removeLast(LinkedList* list) {
    LinkedListNode* temp;
    char* data;

    temp = list->tail;
    /* If the head node of the linked list is null, the list is empty
        We cannot remvve any elements as no elements exist */
    if(list->head != NULL) {
        if(list->head->next == NULL) {
            list->head = NULL;
            list->tail = NULL;
        }
        else if(list->head != NULL) {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
        list->count -= 1; /*We reduce the count of the linked list by 1, as we are removing one entry. */
        data = temp->data; /*The data stord in the node is stored and returned. */
        free(temp); /*We FREE the List Node, as it will no longer be accessed */
    }
    else {
        data = NULL;
        printf("FAILURE: Linked list is currently empty");
    }
    return data;
}

/********************
Function Get Head
Purpose: Returns the head node in a linked list. 
    Used with hasNext and next to iterate through every element
Date: 15/10/20
Author: Austin Bevacqua
*********************/
LinkedListNode* getHead(LinkedList* list) {
    return (list->head);
}

/********************
Function Get Tail
Purpose: Returns the tail node in a linked list. 
Date: 15/10/20
Author: Austin Bevacqua
*********************/
LinkedListNode* getTail(LinkedList* list) {
    return (list->tail);
}

/********************
Function Get Next
Purpose: Returns the next node in the linked list after the imported node
Assertion: A next node exists. if not, the function will return null.
Date: 15/10/20
Author: Austin Bevacqua
*******************/
LinkedListNode* getNext(LinkedListNode* node) {
    return (node->next);
}

/********************
Function Print Linked List
Purpose: Prints the contents of the linked list to the screen
Date: 15/10/20
Author: Austin Bevacqua
*******************/
void printLinkedList(LinkedList* list, listFunc funcPtr) {
    LinkedListNode* currNode;
    currNode = list->head;
    while(currNode != NULL) {
        funcPtr(currNode->data);
        currNode = currNode->next;
    }
}

/*********************
Function Free Linked List
Purpose: Frees every element within the linked list + the linked list itself 
Imports: funcPtr (Function Pointer) - Frees the data contained in the linked list nodes 
Date: 20/10/20
Author: Austin Bevacqua 
*********************/
void freeLinkedList(LinkedList* list, listFunc funcPtr) {
    LinkedListNode* currNode;
    currNode = list->head;
    while(currNode != NULL) { /* The loop continues intil there are no elements remaining */
        funcPtr(removeStart(list)); /*A function is called to free the values stored in the current node */
        currNode = list->head;
    }
    free(list); /* Once all list nodes are freed, we free the linked list itself */
}

void freeEntry(void* data) {
    free(data);
}
