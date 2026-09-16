#include <stdio.h>
#include <stdlib.h>

long long *cube_elements(const int *list, size_t count)
{
    long long *result;
    size_t i;

    if (list == NULL || count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        result[i] = (long long)list[i] * (long long)list[i] * (long long)list[i];
    }

    return result;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, -6};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long *cubes;
    size_t i;

    cubes = cube_elements(numbers, count);
    if (cubes == NULL) {
        fprintf(stderr, "Failed to compute cubes\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%d^3 = %lld\n", numbers[i], cubes[i]) < 0) {
            free(cubes);
            return EXIT_FAILURE;
        }
    }

    free(cubes);
    return EXIT_SUCCESS;
}