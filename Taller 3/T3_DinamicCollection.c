#include <stdio.h>

#define myInfinite 2147483647

void myMerge(int A[], int p, int q, int r) {
    int n1 = q - p + 1, n2 = r - q;
    int i, j, k, L[n1 + 2], R[n2 + 2];
    for (i = 1; i <= n1; i++)
        L[i] = A[p + i - 1];
    for (j = 1; j <= n2; j++)
        R[j] = A[q + j];
    L[n1 + 1] = myInfinite;
    R[n2 + 1] = myInfinite;
    i = 1;
    j = 1;
    for (k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void MergeSort(int A[], int p, int r) {
    int q;
    if (p < r) {
        q = (p + r) >> 1;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
}

int binarySearch(int A[], int i, int j, int k) {
    int m, result = -1;
    while (i <= j) {
        m = (i + j) >> 1;
        if (A[m] == k) {
            result = m;
            break;
        } else {
            if (k > A[m])
                i = m + 1;
            else
                j = m - 1;
        }
    }
    if (result == -1)
        result = (-1) * i - 1;
    return result;
}

int countInRange(int A[], int n, int a, int b) {
    // Si b es mayor que el último elemento en el arreglo, ajustar b al último elemento
    if (b > A[n-1]) {
        b = A[n-1];
    }

    int start = binarySearch(A, 0, n - 1, a);
    int end = binarySearch(A, 0, n - 1, b);

    // Si el valor no está en el arreglo, convertir el resultado negativo al índice de inserción
    if (start < 0) start = (-start) - 1;
    if (end < 0) end = (-end) - 1;

    // Ajustar para incluir los elementos menores o iguales a 'b'
    while (end < n && A[end] <= b) end++;

    return end - start;
}

int main() {
    int n, q, i;
    scanf("%d %d", &n, &q);

    int collection[1000000];
    for (i = 0; i < n; i++) {
        scanf("%d", &collection[i]);
    }

    MergeSort(collection, 0, n - 1);

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int k;
            scanf("%d", &k);
            int pos = binarySearch(collection, 0, n - 1, k);
            if (pos >= 0) {
                // El elemento ya está en la colección, no hacemos nada
                continue;
            } else {
                // Debemos insertar k
                pos = (-pos) - 1; // Convertir a índice de inserción
                if (k > collection[n - 1]) {
                    // Caso 2: k es mayor que todos, añadir al final
                    collection[n++] = k;
                } else {
                    // Caso 3: Reemplazar la primera ocurrencia del elemento mayor a k
                    collection[pos] = k;
                }
                MergeSort(collection, 0, n - 1); // Reordenar después de insertar/reemplazar
            }
        } else if (op == 2) {
            int a, b;
            scanf("%d %d", &a, &b);
            int result = countInRange(collection, n, a, b);
            printf("%d\n", result);
        }
    }

    return 0;
}

