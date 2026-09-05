#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long (*MapFunc)(long long, long long);

long long power_map(long long base, long long index) {
    return (long long)pow(base, index);
}

/* Possible weaknesses found:
 *  Parameter 'indices' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'bases' can be declared as pointer to const [constParameterPointer]
 */
long long* map(long long* bases, long long* indices, long long size) {
    if (bases == NULL || indices == NULL || size <= 0) {
        return NULL;
    }

    long long* result = (long long*)malloc(size * sizeof(long long));
    if (result == NULL) {
        return NULL;
    }

    for (long long i = 0; i < size; i++) {
        result[i] = power_map(bases[i], indices[i]);
    }

    return result;
}

int main() {
    long long bases[] = {2, 3, 5, 10};
    long long indices[] = {3, 4, 2, 1};
    long long size = sizeof(bases) / sizeof(bases[0]);

    long long* result = map(bases, indices, size);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (long long i = 0; i < size; i++) {
        printf("%lld ", result[i]);
    }
    printf("\n");

    free(result);

    return EXIT_SUCCESS;
}