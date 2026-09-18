#include <stdio.h>

long long multiplyAllInList(int* list, size_t len) {
    long long result = 1;
    for (size_t i = 0; i < len; i++) {
        if (list[i] == 0) {
            return 0;
        }
        result *= list[i];
    }
    return result;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(numbers) / sizeof(numbers[0]);
    long long result = multiplyAllInList(numbers, len);
    printf("The result is %lld\n", result);
    return 0;
}