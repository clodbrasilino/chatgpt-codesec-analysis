#include <stdio.h>
#include <stdlib.h>

int count_in_range(int *list, size_t size, int lower, int upper) {
    if (list == NULL || size == 0) {
        return 0;
    }

    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] >= lower && list[i] <= upper) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int *list = NULL;
    size_t size = 0;
    int lower = 0;
    int upper = 0;

    printf("Enter the number of elements: ");
    if (scanf("%zu", &size) != 1) {
        return EXIT_FAILURE;
    }

    if (size > 0) {
        list = (int *)malloc(size * sizeof(int));
        if (list == NULL) {
            return EXIT_FAILURE;
        }

        printf("Enter the elements:\n");
        for (size_t i = 0; i < size; i++) {
            if (scanf("%d", &list[i]) != 1) {
                free(list);
                return EXIT_FAILURE;
            }
        }
    }

    printf("Enter the lower and upper bounds: ");
    if (scanf("%d %d", &lower, &upper) != 2) {
        free(list);
        return EXIT_FAILURE;
    }

    int result = count_in_range(list, size, lower, upper);
    printf("Count: %d\n", result);

    free(list);
    return EXIT_SUCCESS;
}