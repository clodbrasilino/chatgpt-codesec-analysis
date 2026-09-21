#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void sift_down(int *list, size_t length, size_t root)
{
    while (root < length / 2U) {
        size_t left = root * 2U + 1U;
        size_t right = left + 1U;
        size_t smallest = left;

        if (right < length && list[right] < list[left]) {
            smallest = right;
        }

        if (list[root] <= list[smallest]) {
            break;
        }

        int temporary = list[root];
        list[root] = list[smallest];
        list[smallest] = temporary;
        root = smallest;
    }
}

bool heapify(int *list, size_t length)
{
    if (list == NULL && length != 0U) {
        return false;
    }

    for (size_t index = length / 2U; index > 0U; --index) {
        sift_down(list, length, index - 1U);
    }

    return true;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    if (argc < 2) {
        if (fprintf(stderr, "Usage: %s integer [integer ...]\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    size_t length = (size_t)argc - 1U;

    if (length > SIZE_MAX / sizeof(int)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int *list = malloc(length * sizeof(*list));
    if (list == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        char *end = NULL;
        errno = 0;
        long value = strtol(argv[index + 1U], &end, 10);

        if (errno == ERANGE ||
            end == argv[index + 1U] ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argv[index + 1U]);
            free(list);
            return EXIT_FAILURE;
        }

        list[index] = (int)value;
    }

    if (!heapify(list, length)) {
        fputs("Failed to create heap.\n", stderr);
        free(list);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        if (printf("%s%d", index == 0U ? "" : " ", list[index]) < 0) {
            free(list);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}