#include <stdio.h>
#include <stdlib.h>

static long long int_power(long long base, long long exponent)
{
    long long result = 1;
    long long i;

    if (exponent < 0) {
        return 0;
    }

    for (i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'context' can be declared as pointer to const. However it seems that 'power_callback' is a callback function, if 'context' is declared with const you might also need to cast function pointer(s). [constParameterCallback]
 *  Parameter 'context' can be declared as pointer to const
 */
static long long power_callback(long long index, void *context)
{
    const long long *base = (const long long *)context;

    if (base == NULL) {
        return 0;
    }

    return int_power(*base, index);
}

long long *map(const long long *array, size_t size,
               long long (*callback)(long long, void *), void *context)
{
    long long *result;
    size_t i;

    if (array == NULL || callback == NULL || size == 0) {
        return NULL;
    }

    result = (long long *)malloc(size * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < size; i++) {
        result[i] = callback(array[i], context);
    }

    return result;
}

long long *power_list(long long base, size_t size)
{
    long long *indices;
    long long *result;
    size_t i;

    if (size == 0) {
        return NULL;
    }

    indices = (long long *)malloc(size * sizeof(*indices));
    if (indices == NULL) {
        return NULL;
    }

    for (i = 0; i < size; i++) {
        indices[i] = (long long)i;
    }

    /* Possible weaknesses found:
     *  You might need to cast the function pointer here
     */
    result = map(indices, size, power_callback, &base);

    free(indices);

    return result;
}

int main(void)
{
    const long long base = 2;
    const size_t size = 10;
    long long *list;
    size_t i;

    list = power_list(base, size);
    if (list == NULL) {
        fprintf(stderr, "Error: failed to create power list\n");
        return EXIT_FAILURE;
    }

    printf("Powers of %lld:\n", base);
    for (i = 0; i < size; i++) {
        printf("%lld^%zu = %lld\n", base, i, list[i]);
    }

    free(list);

    return EXIT_SUCCESS;
}