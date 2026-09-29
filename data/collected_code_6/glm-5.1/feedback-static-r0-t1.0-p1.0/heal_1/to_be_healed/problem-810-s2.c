#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'elements' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'counts' can be declared as pointer to const [constParameterPointer]
 */
void iterate_with_counts(int *elements, int *counts, size_t size) {
    if (elements == NULL || counts == NULL || size == 0) {
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
    int elements[] = {10, 20, 30, 40};
    int counts[] = {2, 0, 3, 1};
    size_t size = sizeof(elements) / sizeof(elements[0]);

    iterate_with_counts(elements, counts, size);

    return 0;
}