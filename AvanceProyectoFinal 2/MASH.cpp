#include <stdio.h>
#include <stdlib.h>
#define MAX_DECK_SIZE 20

// Estructura del nodo
struct node {
    int data;
    struct node *next;
};

struct node* createList(struct node* head, int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
    
    if (head == NULL) 
        return newNode; 
    

    // Recorrer la lista hasta el ultimo nodo
    struct node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode; 
    return head;
}

// contar los nodos de la lista
int listSize(struct node* head) {
    int count = 0;
    struct node* actual = head;

    while (actual != NULL) {
        count++;
        actual = actual->next;
    }
    return count;
}

// eliminar un nodo en una posicion especifica
struct node* deleteElement(struct node* head, int pos) {
    if (head == NULL) return NULL;

    struct node* temp = head;

    if (pos == 1) {
        head = temp->next;  // Cambiar la cabeza
        free(temp);         // Liberar el nodo eliminado
        return head;
    }

    for (int i = 1; temp != NULL && i < pos - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return head;
    struct node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);

    return head;
}

void printList(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

void solver(int N, int X, int deck[MAX_DECK_SIZE]) {
    struct node* head = NULL;

   
    for (int i = 1; i <= N; i++) 
        head = createList(head, i);
    

    int currentPos = 1;  
    int listSizeCurrent = N;  

    for (int i = 0; i < MAX_DECK_SIZE && listSizeCurrent > X; i++) {
        int count = deck[i];  
        int deletePos = count;  

        while (deletePos <= listSizeCurrent && listSizeCurrent > X) {
            head = deleteElement(head, deletePos);
            listSizeCurrent = listSize(head);
            if (listSizeCurrent <= X) {
                break;
            }
            deletePos = deletePos + count - 1;
        }
    }
    printList(head);
    printf("\n");
}

int main() {
    int N, X, selection_count = 1;
    int deck[MAX_DECK_SIZE];
    while (scanf("%d %d", &N, &X) != EOF) {
        for (int i = 0; i < MAX_DECK_SIZE; i++) 
            scanf("%d", &deck[i]);
        
        printf("Selection #%d\n", selection_count);
        solver(N, X, deck);
        printf("\n");

        selection_count++;
    }
}
