#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct node *InsertElementInAscendentLinkedList(struct node *head, int element);
struct node *DeleteElementOfAscendentLinkedList(struct node *head, int element);
void PrintAscendentList(struct node *head);

struct node {
    int key;
    struct node *next;
};

struct node *InsertElementInAscendentLinkedList(struct node *head, int element) {
    struct node *newNode, *previous, *actual;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;
    if (head == NULL) {
        newNode->next = head;
        head = newNode;
    }
    else {
        if (element <= head->key) {
            newNode->next = head;
            head = newNode;
        }
        else {
            previous = head;
            actual = head->next;
            while (actual != NULL){
                if (element > actual->key){
                    previous = actual;
                    actual = actual->next;
                }
                else
                    break;
            }
            newNode->next = actual;
            previous->next = newNode;
        }
    }
    return head;
}

void PrintAscendentLinkedList(struct node *head){
    struct node *actual;
    actual = head;
    while (actual != NULL){
        printf(" %d -> ", actual->key);
        actual = actual->next;
    }
    printf(" NULL \n");
}

struct node *DeleteElementOfAscendentLinkedList(struct node *head, int element){
    struct node *previous, *actual;
    if (head == NULL)
        printf(" The ascendent linked list is empty .\n");
    else{
        if (element < head->key)
            printf(" The %d is not in the ascendent linked list .\n", element);
        else{
            if (element == head->key) {
                actual = head;
                head = head->next;
                free(actual);
            }
            else {
                previous = head;
                actual = head->next;
                while (actual != NULL) {
                    if (element > actual->key) {
                        previous = actual;
                        actual = actual->next;
                    }
                    else
                        break;
                }
                if (actual == NULL)
                    printf(" The %d is not in the ascendent linked list .\n", element);
                else {
                    if (actual->key != element)
                        printf(" The %d is not in the ascendent linked list .\n", element);
                    else {
                        previous->next = actual->next;
                        free(actual);
                    }
                }
            }
        }
    }
    return head;
}

int main() {
    int operation, element;
    struct node *head;
    head = NULL;
    while (scanf(" %d %d", &operation, &element) != EOF) {
        if (operation == 1) {
            head = InsertElementInAscendentLinkedList(head, element);
            PrintAscendentLinkedList(head);
        }
        else {
            if (operation == 2) {
                head = DeleteElementOfAscendentLinkedList(head, element);
                PrintAscendentLinkedList(head);
            }
            else
                printf(" Bad use . \n 1. Insert \n 2. Delete \n");
        }
    }
    return 0;
}