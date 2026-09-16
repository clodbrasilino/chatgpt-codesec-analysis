#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
void print_duplicates(int *array, size_t size) {
    if (array == NULL || size < 2) {
        return;
    }

    int *visited = calloc(size, sizeof(int));
    if (visited == NULL) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (visited[i] == 1) {
            continue;
        }
        int count = 1;
        for (size_t j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                count++;
                visited[j] = 1;
            }
        }
        if (count > 1) {
            printf("%d\n", array[i]);
        }
    }

    free(visited);
}

int main(void) {
    int list[] = {1, 2, 3, 2, 4, 5, 1, 6, 7, 8, 8, 9};
    size_t size = sizeof(list) / sizeof(list[0]);

    print_duplicates(list, size);

    return 0;
}