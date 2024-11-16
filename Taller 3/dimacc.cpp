#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

void myMerge(vector<int> &A, int p, int q, int r) {
    int n1 = q - p + 1, n2 = r - q;
    int i, j, k;
    vector<int> L(n1 + 2), R(n2 + 2);

    for (i = 1; i <= n1; i++)
        L[i] = A[p + i - 1];

    for (j = 1; j <= n2; j++)
        R[j] = A[q + j];

    L[n1 + 1] = INT_MAX;
    R[n2 + 1] = INT_MAX;
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

void MergeSort(vector<int> &A, int p, int r) {
    int q;
    if (p < r) {
        q = (p + r) >> 1;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
}

int binarySearch(const vector<int> &A, int i, int j, int k) {
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

// Función para contar los elementos en el rango [a, b]
int countInRange(const vector<int> &C, int a, int b) {
    int lower = binarySearch(C, 0, C.size() - 1, a);
    int upper = binarySearch(C, 0, C.size() - 1, b);

    if (lower < 0) lower = -lower - 1; // Si no lo encuentra, da la posición donde debería estar
    if (upper < 0) upper = -upper - 2; // Ajusta para incluir el valor más cercano por debajo de b

    return (upper - lower + 1); // Cantidad de elementos en el rango [a, b]
}
// Funcion para actualizar la coleccon según la operacion 1 v.1
/*
void updateCollection(vector<int> &C, int k) {
    auto it = lower_bound(C.begin(), C.end(), k);
    if (it == C.end() || *it != k) {
        if (it == C.end()) {
            C.push_back(k); // Poner al final del arreglo
        } else {
            *it = k;
        }
        MergeSort(C, 0, C.size() - 1);
    }
}
*/

// actualizar coleccion operacion 1 v.2
void updateCollection(vector<int> &C, int k) {
    int pos = binarySearch(C, 0, C.size() - 1, k);

    // Si el elemento ya existe, no hacemos nada
    if (pos >= 0) {
        return;
    }

    // Si el elemento no existe, encontrar la posición donde insertar
    pos = -pos - 1;

    // Si el elemento es más grande que todos los existentes, añadir al final
    if (pos == C.size()) {
        C.push_back(k);
    } else {
        // Si el elemento es menor que algún existente, reemplazar el primero que sea mayor
        C[pos] = k;
    }
}
int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    vector<int> C(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &C[i]);
    }

    MergeSort(C, 0, n - 1);

    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) { // Operacion 1
            int k;
            scanf("%d", &k);
            updateCollection(C, k);

        } else if (type == 2) { // Operacion 2
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%d\n", countInRange(C, a, b));
        }
    }

    return 0;
}
