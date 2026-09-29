#include <stdio.h>
#include <stdlib.h>

int contains(const int *arr, size_t size, int value)
{
    size_t i;
    for (i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

int *tuple_to_set(const int *tuple, size_t tuple_size, size_t *set_size)
{
    int *set;
    size_t i;
    size_t count = 0;

    if (tuple == NULL || set_size == NULL || tuple_size == 0) {
        if (set_size != NULL) {
            *set_size = 0;
        }
        return NULL;
    }

    set = malloc(tuple_size * sizeof(int));
    if (set == NULL) {
        *set_size = 0;
        return NULL;
    }

    for (i = 0; i < tuple_size; i++) {
        if (!contains(set, count, tuple[i])) {
            set[count] = tuple[i];
            count++;
        }
    }

    *set_size = count;
    return set;
}

int main(void)
{
    int tuple[] = {1, 2, 2, 3, 4, 4, 5, 1};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    size_t set_size = 0;
    size_t i;
    int *set;

    set = tuple_to_set(tuple, tuple_size, &set_size);
    if (set == NULL) {
        fprintf(stderr, "Failed to convert tuple to set\n");
        return EXIT_FAILURE;
    }

    printf("Set: {");
    for (i = 0; i < set_size; i++) {
        printf("%d", set[i]);
        if (i + 1 < set_size) {
            printf(", ");
        }
    }
    printf("}\n");

    free(set);
    return EXIT_SUCCESS;
}