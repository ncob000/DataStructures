#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node {
    int key;
    struct node *next;
    struct node *prev;
};

struct node *insertInCircularDoublyLinkedList(struct node *tail, int element) {
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;

    // Caso 1, lista vacia
    if (tail == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        tail = newNode;
    } else { // Caso dos lista con 2 o mas elementos
        newNode->next = tail->next;
        newNode->prev = tail;
        tail->next = newNode;
        newNode->next->prev = newNode;
        tail = newNode;
    }
    return tail;
}

struct node *deleteFirstNodeInCircularDoublyLinkedList(struct node *tail) {
    struct node *firstNode;
    if (tail == NULL ) 
        printf("The circular linked list is empty\n");
    else {
        if (tail == tail->next) { // Lista circular de un solo node
            free(tail);
            tail = NULL;
        } else { // Lista con dos o mas nodos
            firstNode = tail->next;
            tail->next = firstNode->next;
            tail->next->prev = tail;
            free(firstNode);
        }
    }

    return tail;
}

void printFromFirstToLastCircularDoublyLinkedList(struct node *tail) {
    struct node *actualNode, *firstNode;

    if (tail == NULL)
        printf("NULL\n");
    else {
        actualNode = tail;
        firstNode = tail->next;
        while (actualNode != tail) {
            printf("%d -> ", actualNode->key);
            actualNode = actualNode->prev;
        }
        printf("%d -> ... \n", firstNode->key); // los ... indican que es una lista circular
    }
}


int main() {
    struct node *tail = NULL;
    int operation, element;

    while(scanf("%d", &operation) != EOF) {
        if (operation == 1) { // Insert in circular linked list
            scanf("%d", &element);
            tail = insertInCircularDoublyLinkedList(tail, element);
            printFromFirstToLastCircularDoublyLinkedList(tail);
        } else {
            if (operation == 2) { // Delete of circular linked list
                tail = deleteFirstNodeInCircularDoublyLinkedList(tail);
                printFromFirstToLastCircularDoublyLinkedList(tail);
            }
            else
                printf("Bad use.\n 1. Insert \n 2. Delete\n");
        }
    }

    return 0;
}