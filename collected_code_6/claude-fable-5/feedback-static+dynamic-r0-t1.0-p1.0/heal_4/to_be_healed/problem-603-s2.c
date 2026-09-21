#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

static int *get_lucid_numbers(int n, size_t *count);

static int *get_lucid_numbers(int n, size_t *count)
{
    if (count == NULL || n < 1) {
        return NULL;
    }
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    size_t capacity = (size_t)n;
    size_t len = capacity;

    int *arr = malloc(len * sizeof *arr);
    if (arr == NULL) {
        return NULL;
    }

    int *result = malloc(capacity * sizeof *result);
    if (result == NULL) {
        free(arr);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        arr[i] = (int)(i + 1);
    }

    size_t rcount = 0;
    result[rcount++] = arr[0];

    size_t start = 1;
    while (start < len && rcount < capacity) {
        int step = arr[start];
        if (step <= 0) {
            break;
        }
        result[rcount++] = step;

        size_t write = start;
        size_t idx = 0;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        for (size_t read = start; read < len && read < capacity; read++, idx++) {
            if (idx % (size_t)step != 0) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                if (write >= len || write >= capacity || write > read) {
                    break;
                }
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                arr[write++] = arr[read];
            }
        }
        len = write;
    }

    free(arr);

    if (rcount > 0) {
        int *shrunk = realloc(result, rcount * sizeof *shrunk);
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    *count = rcount;
    return result;
}

int main(int argc, const char *const argv[])
{
    int n = 25;

    if (argc > 1) {
        const char *input = argv[1];
        char *end = NULL;
        errno = 0;
        long value = strtol(input, &end, 10);
        if (errno != 0 || end == input || *end != '\0' ||
            value < 1 || value > INT_MAX) {
            fprintf(stderr, "Invalid input: expected a positive integer\n");
            return EXIT_FAILURE;
        }
        n = (int)value;
    }

    size_t count = 0;
    int *lucid = get_lucid_numbers(n, &count);
    if (lucid == NULL) {
        fprintf(stderr, "Failed to compute lucid numbers\n");
        return EXIT_FAILURE;
    }

    printf("Lucid numbers <= %d:\n", n);
    for (size_t i = 0; i < count; i++) {
        printf("%d ", lucid[i]);
    }
    printf("\n");

    free(lucid);
    return EXIT_SUCCESS;
}