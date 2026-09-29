#include <stdio.h>
#include <stdlib.h>

int count_in_range(const int *list, int list_size, int min, int max) {
    int count = 0;
    for (int i = 0; i < list_size; ++i) {
        if (list[i] >= min && list[i] <= max) {
            count++;
        }
    }
    return count;
}

int main() {
    int list[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int list_size = sizeof(list) / sizeof(list[0]);
    int min = 5;
    int max = 15;
    int result = count_in_range(list, list_size, min, max);
    printf("Number of elements in range [%d, %d]: %d\n", min, max, result);
    return 0;
}