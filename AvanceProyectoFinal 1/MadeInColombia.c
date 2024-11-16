#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Heap;

Heap* create_heap(int capacity) {
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->data = (int*) malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(Heap* heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;

    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;

    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        max_heapify(heap, largest);
    }
}

void min_heapify(Heap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        min_heapify(heap, smallest);
    }
}

void insert_max_heap(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = value;

    while (i != 0 && heap->data[(i - 1) / 2] < heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void insert_min_heap(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = value;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extract_max(Heap* heap) {
    if (heap->size <= 0)
        return -1;

    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }

    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    max_heapify(heap, 0);

    return root;
}

int extract_min(Heap* heap) {
    if (heap->size <= 0)
        return -1;

    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }

    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    min_heapify(heap, 0);

    return root;
}

int get_max(Heap* heap) {
    if (heap->size > 0)
        return heap->data[0];
    return -1;
}

int get_min(Heap* heap) {
    if (heap->size > 0)
        return heap->data[0];
    return -1;
}

int main() {
    int N;
    while (scanf("%d", &N), N != 0) {
        Heap *max_heap = create_heap(N);
        Heap *min_heap = create_heap(N);
        double sum_of_medians = 0.0;

        for (int i = 0; i < N; i++) {
            int num;
            scanf("%d", &num);

            if (max_heap->size == 0 || num <= get_max(max_heap)) {
                insert_max_heap(max_heap, num);
            } else {
                insert_min_heap(min_heap, num);
            }

            // Balance heaps
            if (max_heap->size > min_heap->size + 1) {
                insert_min_heap(min_heap, extract_max(max_heap));
            } else if (min_heap->size > max_heap->size) {
                insert_max_heap(max_heap, extract_min(min_heap));
            }

            int median = get_max(max_heap);
            sum_of_medians += median;
        }

        printf("%.2lf\n", sum_of_medians / N);

        free(max_heap->data);
        free(min_heap->data);
        free(max_heap);
        free(min_heap);
    }
    return 0;
}