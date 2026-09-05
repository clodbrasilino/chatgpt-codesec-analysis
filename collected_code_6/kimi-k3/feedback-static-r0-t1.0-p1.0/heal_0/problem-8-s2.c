#include <stdio.h>
#include <stdlib.h>

void square_elements(int *list, size_t size)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < size; i++) {
        list[i] = list[i] * list[i];
    }
}

int main(void)
{
    size_t size;
    size_t i;
    int *list;

    if (printf("Enter the number of elements: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &size) != 1 || size == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    list = malloc(size * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %zu integers: ", size) < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        if (scanf("%d", &list[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
    }

    square_elements(list, size);

    if (printf("Squares: ") < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        if (printf("%d ", list[i]) < 0) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}