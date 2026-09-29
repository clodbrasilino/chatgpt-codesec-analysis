#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

size_t remove_even(int *arr, size_t size)
{
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    size_t read;
    size_t write;

    if (arr == NULL || size == 0) {
        return 0;
    }

    write = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     *  Assuming that condition 'read<size' is not redundant
     */
    for (read = 0; read < size; read++) {
        /* Possible weaknesses found:
         *  Condition 'read>=size' is always false
         *  Condition 'read>=size' is always false [knownConditionTrueFalse]
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= size || write >= size) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (arr[read] % 2 != 0) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            arr[write] = arr[read];
            write++;
        }
    }

    return write;
}

int main(int argc, const char *argv[])
{
    int *arr;
    size_t size;
    size_t new_size;
    size_t i;
    char *end;
    unsigned long value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoul(argv[1], &end, 10);
    if (errno != 0 || end == argv[1] || *end != '\0' || value > (unsigned long)SIZE_MAX) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }

    size = (size_t)value;

    if (size == 0 || size > SIZE_MAX / sizeof(*arr)) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }

    arr = malloc(size * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'i<size' is not redundant
     */
    for (i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Condition 'i>=size' is always false
         *  Condition 'i>=size' is always false [knownConditionTrueFalse]
         */
        if (i >= size || i >= (size_t)INT_MAX) {
            fprintf(stderr, "Value out of range\n");
            free(arr);
            arr = NULL;
            return EXIT_FAILURE;
        }
        arr[i] = (int)(i + 1);
    }

    printf("Original list: ");
    /* Possible weaknesses found:
     *  outer condition: i<size
     */
    for (i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
         *  opposite inner condition: i>=size
         */
        if (i >= size) {
            break;
        }
        printf("%d ", arr[i]);
    }
    printf("\n");

    new_size = remove_even(arr, size);

    if (new_size > size) {
        fprintf(stderr, "Unexpected result size\n");
        free(arr);
        arr = NULL;
        return EXIT_FAILURE;
    }

    printf("List after removing even numbers: ");
    for (i = 0; i < new_size; i++) {
        if (i >= size) {
            break;
        }
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}