#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long int JohannsFunction(int n) {
    return (unsigned long long int)n * (n + 1) * (n + 2) / 6;
}

int main() {
    int i = 0, n;
    int t;

    scanf("%d", &n);
    while (i < n) {
        scanf("%d", &t);
        printf("%llu\n", JohannsFunction(t));
        i++;
    }

    return 0;
}
