#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXT 500000
int main() {
    // < l j
    int n, q, A[MAXT + 1], idElement, idQuery, s, i, j;
    long long int result;
    scanf("%d %d", &n, &q);

    for (idElement = 1; idElement <= n; idElement++)
        scanf("%d", &A[idElement]);

    for (idQuery = 1; idQuery <= q; idQuery++) {
        scanf("%d", &s);
        result = 0;

        for (i = 1; i < n; i++) {
            for (j = i + 1; j <= n; j++) {
                if ((A[i] + A[j]) <= s)
                    result++;
            }
        }

        printf("%lld\n", result);
    }
    return 0;
}
