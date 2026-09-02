#include <stdio.h>
#include <stdlib.h>

void repeat_elements(const int *elements, const int *counts, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < counts[i]; j++) {
            printf("%d ", elements[i]);
        }
    }
    printf("\n");
}

int main() {
    int elements[] = {1, 2, 3};
    int counts[] = {2, 3, 1};
    int size = sizeof(elements) / sizeof(elements[0]);

    repeat_elements(elements, counts, size);

    return 0;
}