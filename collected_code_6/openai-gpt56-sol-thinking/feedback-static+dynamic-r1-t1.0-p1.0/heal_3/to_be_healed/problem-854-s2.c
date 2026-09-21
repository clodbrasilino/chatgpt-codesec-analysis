#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void sift_down(int *const list, size_t length, size_t root)
{
    while (root < length / 2U) {
        const size_t left = root * 2U + 1U;
        const size_t right = left + 1U;
        size_t smallest = left;

        if (right < length && list[right] < list[left]) {
            smallest = right;
        }

        if (list[root] <= list[smallest]) {
            break;
        }

        const int temporary = list[root];
        list[root] = list[smallest];
        list[smallest] = temporary;
        root = smallest;
    }
}

static bool heapify(int *const list, size_t length)
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
 */
int main(int argc, char *argv[const])
{
    if (argc < 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "heapify";

        if (fprintf(stderr,
                    "Usage: %s integer [integer ...]\n",
                    program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    const size_t length = (size_t)argc - 1U;

    if (length > SIZE_MAX / sizeof(int)) {
        if (fputs("Input is too large.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    int *list = malloc(length * sizeof(*list));

    if (list == NULL) {
        if (fputs("Memory allocation failed.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        const char *const argument = argv[index + 1U];
        char *end = NULL;

        errno = 0;
        const long value = strtol(argument, &end, 10);

        if (errno == ERANGE ||
            end == argument ||
            end == NULL ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {
            if (fprintf(stderr, "Invalid integer: %s\n", argument) < 0) {
                free(list);
                return EXIT_FAILURE;
            }

            free(list);
            return EXIT_FAILURE;
        }

        list[index] = (int)value;
    }

    if (!heapify(list, length)) {
        if (fputs("Failed to create heap.\n", stderr) == EOF) {
            free(list);
            return EXIT_FAILURE;
        }

        free(list);
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        /* Possible weaknesses found:
         * Flawfinder printf: If format strings can be influenced by an attacker, they can be exploited (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        if (printf(index == 0U ? "%d" : " %d", list[index]) < 0) {
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