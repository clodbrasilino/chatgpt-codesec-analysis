#include <stdio.h>
#include <stdlib.h>

long long combineIntegers(const int *list, int size) {
    long long result = 0;
    for (int i = 0; i < size; ++i) {
        result = result * 10 + list[i];
    }
    return result;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    long long combined = combineIntegers(list, size);
    printf("%lld\n", combined);
    return 0;
}