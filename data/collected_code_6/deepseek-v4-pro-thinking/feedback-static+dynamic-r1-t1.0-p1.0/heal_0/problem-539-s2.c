#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef long long (*map_fn)(size_t index, void *context);

typedef struct {
    long long base;
} power_context;

static long long power_at(size_t index, void *context) {
    const power_context *ctx = context;
    long long base = ctx->base;
    long long result = 1;

    for (size_t i = 0; i < index; ++i) {
        result *= base;
    }

    return result;
}

static long long *map(size_t count, map_fn fn, void *context) {
    long long *result;

    if (count > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        result[i] = fn(i, context);
    }

    return result;
}

long long *create_powers(long long base, size_t count) {
    power_context context;

    context.base = base;

    return map(count, power_at, &context);
}

int main(void) {
    long long base = 2;
    size_t count = 10;
    long long *powers = create_powers(base, count);

    if (powers == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("%lld ", powers[i]);
    }
    printf("\n");

    free(powers);

    return EXIT_SUCCESS;
}