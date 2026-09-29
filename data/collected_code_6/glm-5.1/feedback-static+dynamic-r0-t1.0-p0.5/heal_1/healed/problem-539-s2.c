#include <stdio.h>
#include <stdlib.h>

typedef long long (*MapFunc)(long long, long long);

long long power_map(long long base, long long index) {
    long long result = 1;
    long long abs_index = index < 0 ? -index : index;
    for (long long i = 0; i < abs_index; i++) {
        result *= base;
    }
    return index < 0 ? 0 : result;
}

long long *map_power(const long long *bases, const long long *indices, size_t size) {
    if (bases == NULL || indices == NULL || size == 0) {
        return NULL;
    }

    long long *result = (long long *)malloc(size * sizeof(long long));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (bases[i] == 0 && indices[i] < 0) {
            free(result);
            return NULL;
        }
        result[i] = power_map(bases[i], indices[i]);
    }

    return result;
}

int main(void) {
    const long long bases[] = {2, 3, 5, 10};
    const long long indices[] = {3, 4, 0, 1};
    size_t size = sizeof(bases) / sizeof(bases[0]);

    long long *result = map_power(bases, indices, size);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%lld ", result[i]);
    }
    printf("\n");

    free(result);

    return EXIT_SUCCESS;
}