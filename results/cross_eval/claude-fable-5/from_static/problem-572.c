#include <stdio.h>
#include <stdlib.h>

int remove_duplicates(int *arr, int size)
{
    int i;
    int j;
    int k;
    int new_size;

    if (arr == NULL || size <= 0) {
        return 0;
    }

    new_size = size;
    for (i = 0; i < new_size; i++) {
        for (j = i + 1; j < new_size; ) {
            if (arr[i] == arr[j]) {
                for (k = j; k < new_size - 1; k++) {
                    arr[k] = arr[k + 1];
                }
                new_size--;
            } else {
                j++;
            }
        }
    }
    return new_size;
}

int process_list(void)
{
    int *list;
    int size;
    int i;
    int new_size;

    if (scanf("%d", &size) != 1) {
        return -1;
    }
    if (size <= 0 || size > 100000) {
        return -1;
    }

    list = malloc((size_t)size * sizeof(int));
    if (list == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        if (scanf("%d", &list[i]) != 1) {
            free(list);
            return -1;
        }
    }

    new_size = remove_duplicates(list, size);

    for (i = 0; i < new_size; i++) {
        if (printf("%d ", list[i]) < 0) {
            free(list);
            return -1;
        }
    }
    if (printf("\n") < 0) {
        free(list);
        return -1;
    }

    free(list);
    return 0;
}

int main(void)
{
    int num_lists;
    int i;

    if (scanf("%d", &num_lists) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (num_lists <= 0 || num_lists > 1000) {
        fprintf(stderr, "Invalid number of lists\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < num_lists; i++) {
        if (process_list() != 0) {
            fprintf(stderr, "Failed to process list %d\n", i + 1);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}