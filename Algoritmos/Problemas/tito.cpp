#include <stdio.h>
#include <vector>

using namespace std;

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

    int N, Q;
    vector<int> chimpH;
    vector<int> titoH;

    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &chimpH[i]);

    scanf("%d", &Q);
    for (int j = 0; j < Q; j++)
        scanf("%d", &titoH[j]);

    for (int i = 0; i < Q; i++) {
        int pos = binarySearch(chimpH, 0, Q, titoH[i]);
        printf("%d", pos);
    }
}