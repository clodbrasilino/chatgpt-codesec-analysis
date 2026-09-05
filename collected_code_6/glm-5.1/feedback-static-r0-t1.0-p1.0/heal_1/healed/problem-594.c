#include <stdio.h>
#include <stdlib.h>

int find_difference(const int *list, size_t size) {
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    for (size_t i = 0; i < size; i++) {
        if (!even_found && list[i] % 2 == 0) {
            first_even = list[i];
            even_found = 1;
        } else if (!odd_found && list[i] % 2 != 0) {
            first_odd = list[i];
            odd_found = 1;
        }

        if (even_found && odd_found) {
            break;
        }
    }

    if (!even_found) {
        first_even = 0;
    }

    if (!odd_found) {
        first_odd = 0;
    }

    return first_even - first_odd;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    size_t size = (size_t)argc - 1;
    int *list = (int *)malloc(size * sizeof(int));
    if (list == NULL) {
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        list[i] = atoi(argv[i + 1]);
    }

    int difference = find_difference(list, size);
    printf("%d\n", difference);

    free(list);
    list = NULL;

    return 0;
}