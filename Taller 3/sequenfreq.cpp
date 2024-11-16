#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
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

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    vector<int> A(n);
    vector<int> S(k);
    vector<int> sums(k);
    vector<int> frequ(k, 0); //Iniciar elementos en 0


    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }


    for (int i = 0; i < k; i++) {
        scanf("%d", &S[i]);
        sums[i] = S[i];
    }


    MergeSort(A, 0, n - 1);

    for (int idx = 0; idx < k; idx++) {
        int si = S[idx];
        int left = 0, right = n - 1;

        while (left < right) {
            int sum = A[left] + A[right];
            if (sum == si) {
                frequ[idx]++;
                left++;
                right--;
            } else if (sum < si) {
                left++;
            } else {
                right--;
            }
        }
    }


    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (frequ[i] < frequ[j] ||
                (frequ[i] == frequ[j] && sums[i] > sums[j])) {
                swap(frequ[i], frequ[j]); // Intercambiar valores
                swap(sums[i], sums[j]);
            }
        }
    }


    for (int i = 0; i < k; i++) {
        printf("%d %d\n", sums[i], frequ[i]);
    }

    return 0;
}
