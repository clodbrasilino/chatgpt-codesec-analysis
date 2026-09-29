#include <stdio.h>
#include <stdlib.h>

void square_elements(int *list, int size) {
    for (int i = 0; i < size; i++) {
        list[i] = list[i] * list[i];
    }
}

int main(void) {
    int size;
    int *list;

    printf("Enter number of elements: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    list = malloc((size_t)size * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &list[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
    }

    square_elements(list, size);

    printf("Squared elements:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return EXIT_SUCCESS;
}