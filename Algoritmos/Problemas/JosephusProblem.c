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

int solver(int n, int k) {
    struct node *tail = NULL, *actualNode;
    int i, idSoldier, idMovement, josephusPosition;

    // Crear lista cirucular con n elementos
    for (i = 1; i <= n; i++)
        tail = insetInCircularLinkedList(tail, i);

    for (idSoldier = 1; idSoldier < n; idSoldier++){
        for (idMovement = 1; idMovement < k; idMovement++)
            tail = tail->next;
        
        /*
        actualNode = tail->next;
        tail->next = actualNode->next;
        free(actualNode);
        */
        tail = deleteFirstNodeInCircularLinkedList(tail);
        PrintCircularLinkedList(tail);
    }
    josephusPosition = tail->key;
    tail = deleteFirstNodeInCircularLinkedList(tail);
    return josephusPosition;
}


int main() {
    
    int n, k;

    while(scanf("%d %d", &n, &k) && n > 0 && k > 0) 
        printf("%d\n", solver(n, k));

    return 0;
}