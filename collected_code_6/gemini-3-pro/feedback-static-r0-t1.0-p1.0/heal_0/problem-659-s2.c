#include <stdio.h>
#include <stdlib.h>

void print_duplicates(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return;
    }

    int *visited = (int *)calloc(size, sizeof(int));
    if (visited == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (visited[i] == 1) {
            continue;
        }

        int is_duplicate = 0;
        for (size_t j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                is_duplicate = 1;
                visited[j] = 1;
            }
        }

        if (is_duplicate) {
            printf("%d\n", array[i]);
        }
    }

    free(visited);
}

int main(void) {
    int my_list[] = {1, 2, 3, 4, 2, 5, 1, 6, 3};
    size_t size = sizeof(my_list) / sizeof(my_list[0]);

    print_duplicates(my_list, size);

    return 0;
}