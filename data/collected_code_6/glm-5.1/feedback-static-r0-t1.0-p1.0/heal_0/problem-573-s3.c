#include <stdio.h>
#include <stdlib.h>

int calculate_unique_product(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    int *seen = malloc(size * sizeof(int));
    if (seen == NULL) {
        return 0;
    }

    size_t seen_size = 0;
    int product = 1;

    for (size_t i = 0; i < size; i++) {
        int is_unique = 1;
        for (size_t j = 0; j < seen_size; j++) {
            if (list[i] == seen[j]) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            product *= list[i];
            seen[seen_size] = list[i];
            seen_size++;
        }
    }

    free(seen);
    return product;
}

int main(void) {
    int list[] = {2, 3, 2, 5, 4, 5, 3, 7};
    size_t size = sizeof(list) / sizeof(list[0]);

    int result = calculate_unique_product(list, size);

    printf("%d\n", result);

    return 0;
}