#include <stdio.h>
#include <stdlib.h>

size_t count_integers(const int *list, size_t size) {
    size_t count = 0;
    if (list == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        count++;
    }
    return count;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t count = count_integers(list, size);
    printf("Count: %zu\n", count);
    return 0;
}