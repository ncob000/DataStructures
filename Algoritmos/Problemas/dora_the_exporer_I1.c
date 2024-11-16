#include <stdio.h>

int main() {
    unsigned long long int n;
    int diagonal = 1, stepDiagonal = n, row, col;

    while (scanf("%llu", &n) && n != 0)
        ;
    while (stepDiagonal > diagonal) {
        stepDiagonal -= diagonal;
        diagonal++;
    }

    if (diagonal % 2 == 0) {
        row = stepDiagonal;
        col = diagonal - stepDiagonal + 1;
        printf("%d %d", row, col);
    } else {
        row = diagonal - stepDiagonal + 1;
        col = stepDiagonal;
        printf("%d %d", row, col);
    }

    return 0;
}
