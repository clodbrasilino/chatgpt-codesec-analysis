#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
void findDifferences(int *numbers, int size) {
    for (int i = 0; i < size - 1; i++) {
        printf("%d ", numbers[i + 1] - numbers[i]);
    }
    printf("\n");
}

int main() {
    int size;
    scanf("%d", &size);
    if (size <= 0) {
        return 1;
    }

    int *numbers = (int *)malloc(size * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        scanf("%d", &numbers[i]);
    }

    findDifferences(numbers, size);

    free(numbers);
    return 0;
}