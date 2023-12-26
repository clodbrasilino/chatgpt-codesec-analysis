#include <stdio.h>

int multiplyList(const int list[], int size) {
    int result = 1;
    for (int i = 0; i < size; i++) {
        result *= list[i];
    }
    return result;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    int multiplied = multiplyList(list, size);
    printf("Result: %d\n", multiplied);
    return 0;
}