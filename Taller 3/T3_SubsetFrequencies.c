#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000000
#define MAXK 50

#define myInfinite 2147483647

// l j k < >
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

void sort(int arr[], int n) { MergeSort(arr, 0, n - 1); }

void sortResults(int sums[], int freqs[], int k) {
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < k - i - 1; j++) {
            if (freqs[j] < freqs[j + 1]) {

                int tempFreq = freqs[j];
                freqs[j] = freqs[j + 1];
                freqs[j + 1] = tempFreq;

                int tempSum = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = tempSum;
            } else if (freqs[j] == freqs[j + 1] && sums[j] > sums[j + 1]) {

                int tempSum = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = tempSum;
            }
        }
    }
}

int main() {
    int n, k;
    int A[MAXN];
    int S[MAXK];
    int sums[MAXK];
    int freqs[MAXK] = {0};

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < k; i++) {
        scanf("%d", &S[i]);
        sums[i] = S[i]; // Almacenar las sumas en el array sums
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int sum = A[i] + A[j];

            for (int x = 0; x < k; x++) {
                if (sum == S[x]) {
                    freqs[x]++;
                }
            }
        }
    }

    //sortResults(sums, freqs, k);

    for (int i = 0; i < k; i++) {
        printf("%d %d\n", sums[i], freqs[i]);
    }

    return 0;
}
