#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {

    long long int n;
    int Sum = 0, i = 0;
    cin >> n;

    do {
        Sum = (i * (i + 1)) / 2;
        i++;
    } while (Sum < n);

    if (Sum == n)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
