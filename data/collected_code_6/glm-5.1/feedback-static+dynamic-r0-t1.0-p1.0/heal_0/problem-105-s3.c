#include <stdio.h>
#include <stdlib.h>

size_t count_true_booleans(const int *list, size_t size) {
    size_t count = 0;
    if (list != NULL) {
        for (size_t i = 0; i < size; i++) {
            if (list[i] != 0) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    int list[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t true_count = count_true_booleans(list, size);
    printf("%zu\n", true_count);
    return EXIT_SUCCESS;
}