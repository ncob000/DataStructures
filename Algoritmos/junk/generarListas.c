#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main();

struct node {
    int key;
    struct node *next;
};

int main() {
    int n;
    struct node *head=NULL, *actualNode, *newNode;

    printf("Valor de n: ");
    scanf("%d", &n);

    while(n >= 1) {
        newNode = (struct node *)malloc(sizeof(struct node));
        newNode->key = n;
        newNode->next = head;
        head = newNode;
        n--;
    }

    actualNode = head;
    while (actualNode != NULL) {
        printf("%d -> ", actualNode->key);
        actualNode = actualNode->next;
    }

    printf("NULL\n");
    actualNode = head;
    while (actualNode != NULL) {
        actualNode = actualNode->next;
        free(head);
        head = actualNode;
    }
    head = NULL;
    return 0;
}