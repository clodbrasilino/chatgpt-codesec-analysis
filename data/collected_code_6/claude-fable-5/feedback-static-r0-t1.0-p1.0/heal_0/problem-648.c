#include <stdio.h>
#include <stdlib.h>

void exchange_pairs(int *list, size_t size)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i + 1 < size; i += 2) {
        int temp = list[i];
        list[i] = list[i + 1];
        list[i + 1] = temp;
    }
}

void print_list(const int *list, size_t size)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < size; i++) {
        printf("%d", list[i]);
        if (i + 1 < size) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void)
{
    size_t size = 7;
    int *list;
    size_t i;

    list = malloc(size * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        list[i] = (int)(i + 1);
    }

    printf("Original list: ");
    print_list(list, size);

    exchange_pairs(list, size);

    printf("Exchanged list: ");
    print_list(list, size);

    free(list);
    list = NULL;

    return EXIT_SUCCESS;
}