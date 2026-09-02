#include <stdio.h>

int count_positive_numbers(const int *list, int length) {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (list[i] > 0) {
            ++count;
        }
    }
    return count;
}

int main() {
    int list[] = {1, -2, 3, -4, 5, -6, 7};
    int length = sizeof(list) / sizeof(list[0]);
    int result = count_positive_numbers(list, length);
    printf("Number of positive numbers: %d\n", result);
    return 0;
}