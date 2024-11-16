#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_HEAP_SIZE 200000

typedef struct {
    int transactionType;
    long int transactionTime;
    int triage;     // priority
    char name[21];  
} transactionInfo;

transactionInfo heap[MAX_HEAP_SIZE];
int heapSize = 0;

int Parent(int i);
int Left(int i);
int Right(int i);
void MinHeapify(transactionInfo heap[], int i, int heapSize);
void MinPQ_Insert(transactionInfo heap[], transactionInfo user, int *heapSize);
transactionInfo MinPQ_Extract(transactionInfo heap[], int *heapSize);
void Swap(transactionInfo *a, transactionInfo *b);

int Parent(int i) { return (i - 1) / 2; }
int Left(int i) { return (2 * i) + 1; }
int Right(int i) { return (2 * i) + 2; }

void Swap(transactionInfo *a, transactionInfo *b) {
    transactionInfo temp = *a;
    *a = *b;
    *b = temp;
}

void MinHeapify(transactionInfo heap[], int i, int heapSize) {
    int left = Left(i);
    int right = Right(i);
    int smallest = i;

    // Comparar prioridad triage y luego por tiempo de llegada
    if (left < heapSize && (heap[left].triage < heap[smallest].triage ||
                            (heap[left].triage == heap[smallest].triage &&
                             heap[left].transactionTime < heap[smallest].transactionTime))) {
        smallest = left;
    }
    if (right < heapSize && (heap[right].triage < heap[smallest].triage ||
                             (heap[right].triage == heap[smallest].triage &&
                              heap[right].transactionTime < heap[smallest].transactionTime))) {
        smallest = right;
    }

    if (smallest != i) {
        Swap(&heap[i], &heap[smallest]);
        MinHeapify(heap, smallest, heapSize);
    }
}

void MinPQ_Insert(transactionInfo heap[], transactionInfo user, int *heapSize) {
    (*heapSize)++;
    heap[*heapSize - 1] = user;  

    int i = *heapSize - 1;
    while (i > 0 && (heap[Parent(i)].triage > heap[i].triage || 
                     (heap[Parent(i)].triage == heap[i].triage &&
                      heap[Parent(i)].transactionTime > heap[i].transactionTime))) {
        Swap(&heap[i], &heap[Parent(i)]);
        i = Parent(i);
    }
}

transactionInfo MinPQ_Extract(transactionInfo heap[], int *heapSize) {
    if (*heapSize <= 0) {
        transactionInfo empty = {0, 0, 0, ""};
        return empty;
    }

    transactionInfo min = heap[0];
    heap[0] = heap[*heapSize - 1];  
    (*heapSize)--;

    MinHeapify(heap, 0, *heapSize);  
    return min;
}

int main() {
    int numTransactions;

    while (scanf("%d", &numTransactions) != EOF) {
        for (int i = 0; i < numTransactions; i++) {
            transactionInfo transaction;
            scanf("%d", &transaction.transactionType);
            
            if (transaction.transactionType == 1) {
                scanf("%d %d %s", &transaction.transactionTime, &transaction.triage, transaction.name);
                MinPQ_Insert(heap, transaction, &heapSize);

            } else if (transaction.transactionType == 2) {
                int attentionTime;
                scanf("%d", &attentionTime);
                transactionInfo user = MinPQ_Extract(heap, &heapSize);
                
                if (strlen(user.name) > 0) {
                    printf("%d %d %d %s\n", user.transactionTime, attentionTime, attentionTime - user.transactionTime, user.name);
                }
            }
        }
        // Reiniciar el heap
        heapSize = 0;
    }

    return 0;
}
