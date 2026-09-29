#include <stdio.h>
#include <stdlib.h>

void iterate_elements(const int *elements, const int *counts, size_t size) {
    if (elements == NULL || counts == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        if (counts[i] < 0) {
            continue;
        }
        for (int j = 0; j < counts[i]; j++) {
            printf("%d\n", elements[i]);
        }
    }
}

int main(void) {
    int elements[] = {1, 2, 3};
    int counts[] = {2, 0, 3};
    size_t size = sizeof(elements) / sizeof(elements[0]);

    iterate_elements(elements, counts, size);

    return 0;
}