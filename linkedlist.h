/* Header guard */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* Typedef for the Linked List Node struct */
typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode;

/* Typedef for the Linked List struct */
typedef struct {
    int count;
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;

/* Functiom pointer typedef */
typedef void (*listFunc)(void* data);

/* Function declairations */
LinkedList* createLinkedList();
void* findAt(LinkedList*, int);
void insertStart(LinkedList*, void*);
void insertLast(LinkedList*, void*);
void* removeStart(LinkedList*);
void* removeLast(LinkedList* list);
LinkedListNode* getHead(LinkedList*);
LinkedListNode* getTail(LinkedList*);
LinkedListNode* getNext(LinkedListNode*);
void printLinkedList(LinkedList* list, listFunc funcPtr);
void freeLinkedList(LinkedList* list, listFunc funcPtr);
void freeEntry(void*);
#endif
