#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

size_t remove_even(int *arr, size_t size, size_t capacity)
{
    size_t read;
    size_t write;

    if (arr == NULL || capacity == 0 || size > capacity) {
        return 0;
    }

    write = 0;
    for (read = 0; read < size && read < capacity; read++) {
        if (write >= capacity) {
            break;
        }
        if (arr[read] % 2 != 0) {
            arr[write] = arr[read];
            write++;
        }
    }

    return write;
}

int main(int argc, const char * const argv[])
{
    int *arr;
    size_t size;
    size_t new_size;
    size_t i;
    char *endptr;
    long parsed;
    const char *progname;

    progname = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <size>\n", progname);
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    parsed = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' ||
        parsed <= 0 || parsed > INT_MAX) {
        fprintf(stderr, "Invalid size\n");
        return EXIT_FAILURE;
    }

    size = (size_t)parsed;

    if (size > SIZE_MAX / sizeof(*arr)) {
        fprintf(stderr, "Invalid size\n");
        return EXIT_FAILURE;
    }

    arr = malloc(size * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        arr[i] = (int)(i + 1);
    }

    printf("Original list: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    new_size = remove_even(arr, size, size);

    if (new_size > size) {
        new_size = size;
    }

    printf("List after removing even numbers: ");
    for (i = 0; i < new_size && i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}