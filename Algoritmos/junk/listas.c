#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct node {
    int key;
    struct node *next;
};

int main () {
    struct node *head, *q;
    head = (struct node *)malloc(sizeof(struct node));
    head->key = 1;
    q = (struct node *)malloc(sizeof(struct node));
    q->key = 2;
    head->next = q;
    q->next = (struct node *)malloc(sizeof(struct node));
    q->next->key = 3;
    q->next->next = NULL;
    printf("%d -> %d -> %d\n",
           head->key,
           head->next->key,
           head->next->next->key);
    return 0;
}