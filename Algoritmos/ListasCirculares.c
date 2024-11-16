#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node {
    int key;
    struct node *next;
};

struct node *insetInCircularLinkedList(struct node *tail, int element) {
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;

    // Caso 1, lista vacia
    if (tail == NULL) {
        newNode->next = newNode;
        tail = newNode;
    } else { // Caso dos lista con elementos
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
    return tail;
}

struct node *deleteFirstNodeInCircularLinkedList(struct node *tail) {
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
            free(firstNode);
        }
    }

    return tail;
}

void PrintCircularLinkedList(struct node *tail) {
    struct node *actualNode;

    if (tail == NULL)
        printf("NULL\n");
    else {
        actualNode = tail->next;
        while (actualNode != tail) {
            printf("%d -> ", actualNode->key);
            actualNode = actualNode->next;
        }
        printf("%d -> ... \n", tail->key); // los ... indican que es una lista circular
    }
}


int main() {
    struct node *tail = NULL;
    int operation, element;

    while(scanf("%d", &operation) != EOF) {
        if (operation == 1) { // Insert in circular linked list
            scanf("%d", &element);
            tail = insetInCircularLinkedList(tail, element);
            PrintCircularLinkedList(tail);
        } else {
            if (operation == 2) { // Delete of circular linked list
                tail = deleteFirstNodeInCircularLinkedList(tail);
                PrintCircularLinkedList(tail);
            }
            else
                printf("Bad use.\n 1. Insert \n 2. Delete\n");
        }
    }

    return 0;
}