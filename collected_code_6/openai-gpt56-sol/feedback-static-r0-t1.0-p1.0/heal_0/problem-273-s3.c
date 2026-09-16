#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t length;
    long long *values;
} Tuple;

static int tuple_create(Tuple *tuple, size_t length)
{
    if (tuple == NULL || length == 0 || length > SIZE_MAX / sizeof(*tuple->values)) {
        return -1;
    }

    tuple->values = calloc(length, sizeof(*tuple->values));
    if (tuple->values == NULL) {
        tuple->length = 0;
        return -1;
    }

    tuple->length = length;
    return 0;
}

static void tuple_destroy(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->length = 0;
    }
}

static int tuple_subtract(const Tuple *left, const Tuple *right, Tuple *result)
{
    if (left == NULL || right == NULL || result == NULL ||
        left->values == NULL || right->values == NULL ||
        left->length == 0 || left->length != right->length) {
        return -1;
    }

    if (tuple_create(result, left->length) != 0) {
        return -1;
    }

    for (size_t i = 0; i < left->length; ++i) {
        if (__builtin_sub_overflow(left->values[i], right->values[i],
                                   &result->values[i])) {
            tuple_destroy(result);
            return -1;
        }
    }

    return 0;
}

static int read_tuple(Tuple *tuple, const char *name)
{
    if (tuple == NULL || tuple->values == NULL || name == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple->length; ++i) {
        printf("%s[%zu]: ", name, i);
        if (fflush(stdout) == EOF ||
            scanf("%lld", &tuple->values[i]) != 1) {
            return -1;
        }
    }

    return 0;
}

static void print_tuple(const Tuple *tuple)
{
    if (tuple == NULL || tuple->values == NULL) {
        return;
    }

    putchar('(');
    for (size_t i = 0; i < tuple->length; ++i) {
        printf("%lld%s", tuple->values[i],
               i + 1 == tuple->length ? "" : ", ");
    }
    puts(")");
}

int main(void)
{
    Tuple left = {0, NULL};
    Tuple right = {0, NULL};
    Tuple result = {0, NULL};
    size_t length = 0;
    int status = EXIT_FAILURE;

    printf("Tuple length: ");
    if (fflush(stdout) == EOF || scanf("%zu", &length) != 1 || length == 0) {
        fputs("Invalid tuple length.\n", stderr);
        goto cleanup;
    }

    if (tuple_create(&left, length) != 0 ||
        tuple_create(&right, length) != 0) {
        fputs("Unable to allocate tuples.\n", stderr);
        goto cleanup;
    }

    if (read_tuple(&left, "left") != 0 ||
        read_tuple(&right, "right") != 0) {
        fputs("Invalid tuple value.\n", stderr);
        goto cleanup;
    }

    if (tuple_subtract(&left, &right, &result) != 0) {
        fputs("Tuple subtraction failed.\n", stderr);
        goto cleanup;
    }

    print_tuple(&result);
    status = EXIT_SUCCESS;

cleanup:
    tuple_destroy(&result);
    tuple_destroy(&right);
    tuple_destroy(&left);
    return status;
}