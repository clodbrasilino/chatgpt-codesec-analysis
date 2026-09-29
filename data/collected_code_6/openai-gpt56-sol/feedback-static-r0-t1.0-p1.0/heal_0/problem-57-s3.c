#include <stdio.h>
#include <stdlib.h>

static int compare_descending(const void *left, const void *right)
{
    const char a = *(const char *)left;
    const char b = *(const char *)right;

    return (a < b) - (a > b);
}

static char *largest_number(const int digits[], size_t count)
{
    char *result;
    size_t i;

    if (digits == NULL || count == 0 || count > SIZE_MAX - 1) {
        return NULL;
    }

    result = malloc(count + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        if (digits[i] < 0 || digits[i] > 9) {
            free(result);
            return NULL;
        }
        result[i] = (char)('0' + digits[i]);
    }

    qsort(result, count, sizeof(*result), compare_descending);
    result[count] = '\0';

    return result;
}

int main(void)
{
    size_t count;
    size_t i;
    int *digits = NULL;
    char *number = NULL;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(*digits)) {
        goto cleanup;
    }

    digits = malloc(count * sizeof(*digits));
    if (digits == NULL) {
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        if (scanf("%d", &digits[i]) != 1 ||
            digits[i] < 0 || digits[i] > 9) {
            goto cleanup;
        }
    }

    number = largest_number(digits, count);
    if (number == NULL) {
        goto cleanup;
    }

    if (printf("%s\n", number) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(number);
    free(digits);
    return status;
}