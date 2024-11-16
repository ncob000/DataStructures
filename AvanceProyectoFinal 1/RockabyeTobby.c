#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define myNegativeInfinite -2147483647
#define myPositiveInfinite 2147483647
#define MAXT 1000
#define MAXN 100005

typedef struct {
    char name[16];
    int period;   
    int next_time;
    int priority;
} Medication;

int Parent(int i) { return i >> 1; }
int Left(int i) { return i << 1; }
int Right(int i) { return (i << 1) + 1; }

void MinHeapify(int Q[], Medication meds[], int i, int heapSize) {
    int l, r, least, temp;
    l = Left(i);
    r = Right(i);
    
    if ((l <= heapSize) && 
        (meds[Q[l]].next_time < meds[Q[i]].next_time || 
        (meds[Q[l]].next_time == meds[Q[i]].next_time && meds[Q[l]].priority < meds[Q[i]].priority))) {
        least = l;
    } else {
        least = i;
    }
    
    if ((r <= heapSize) && 
        (meds[Q[r]].next_time < meds[Q[least]].next_time || 
        (meds[Q[r]].next_time == meds[Q[least]].next_time && meds[Q[r]].priority < meds[Q[least]].priority))) {
        least = r;
    }
    
    if (least != i) {
        temp = Q[i];
        Q[i] = Q[least];
        Q[least] = temp;
        MinHeapify(Q, meds, least, heapSize);
    }
}

int MinPQ_Extract(int Q[], Medication meds[], int *heapSize) {
    int min = myNegativeInfinite;
    if (*heapSize < 1) {
        printf("Heap underflow.\n");
    } else {
        min = Q[1]; 
        Q[1] = Q[*heapSize];
        (*heapSize)--;
        MinHeapify(Q, meds, 1, *heapSize);
    }
    return min;
}

void MinPQ_DecreaseKey(int Q[], Medication meds[], int i, int key, int priority) {
    int temp;
    if (key > meds[Q[i]].next_time) {
        printf("New key is higher than current key.\n");
    } else {
        meds[Q[i]].next_time = key;
        meds[Q[i]].priority = priority;
        while ((i > 1) && 
               (meds[Q[Parent(i)]].next_time > meds[Q[i]].next_time || 
               (meds[Q[Parent(i)]].next_time == meds[Q[i]].next_time && meds[Q[Parent(i)]].priority > meds[Q[i]].priority))) {
            temp = Q[i];
            Q[i] = Q[Parent(i)];
            Q[Parent(i)] = temp;
            i = Parent(i);
        }
    }
}

void MinPQ_Insert(int Q[], Medication meds[], int index, int *heapSize) {
    (*heapSize)++;
    Q[*heapSize] = index;
    MinPQ_DecreaseKey(Q, meds, *heapSize, meds[index].next_time, meds[index].priority);
}

int main() {
    int t;
    scanf("%d", &t);

    for (int case_num = 0; case_num < t; case_num++) {
        int n, k;
        scanf("%d %d", &n, &k);

        Medication meds[MAXN]; 
        int Q[MAXN];           // almacenar indices de medicamentos
        int heapSize = 0;

        for (int i = 0; i < n; i++) {
            scanf("%s %d", meds[i].name, &meds[i].period);
            meds[i].next_time = meds[i].period;
            meds[i].priority = i;  
            MinPQ_Insert(Q, meds, i, &heapSize);
        }

        for (int i = 0; i < k; i++) {
            int minIndex = MinPQ_Extract(Q, meds, &heapSize);
            Medication med = meds[minIndex];

            printf("%d %s\n", med.next_time, med.name);

            med.next_time += med.period;
            meds[minIndex] = med;
            MinPQ_Insert(Q, meds, minIndex, &heapSize);
        }
    }

    return 0;
}