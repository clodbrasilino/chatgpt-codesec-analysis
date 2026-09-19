#include <stdio.h>
#include <stdlib.h>

size_t find_frequency(const int *array, size_t size, int target) {
    size_t count = 0;
    if (array != NULL && size > 0) {
        for (size_t i = 0; i < size; i++) {
            if (array[i] == target) {
                count++;
            }
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    int target = atoi(argv[1]);

    int array[] = {1, 2, 3, 4, 2, 5, 2, 8, 9, 2};
    size_t size = sizeof(array) / sizeof(array[0]);

    size_t frequency = find_frequency(array, size, target);

    printf("%zu\n", frequency);

    return EXIT_SUCCESS;
}