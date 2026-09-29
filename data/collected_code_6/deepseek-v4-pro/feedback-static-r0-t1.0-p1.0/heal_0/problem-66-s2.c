#include <stdio.h>
#include <stdlib.h>

int count_positive(const int *list, size_t size) {
    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] > 0) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    int test_list[] = {1, -2, 3, 0, 4, -5, 6};
    size_t test_size = sizeof(test_list) / sizeof(test_list[0]);
    int result = count_positive(test_list, test_size);
    printf("Positive count: %d\n", result);
    return 0;
}