#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void sift_down(int *list, size_t length, size_t root)
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
 */
static int run(int argc, char *const argv[const])
{
    if (argc < 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr,
                    "Usage: %s integer [integer ...]\n",
                    program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    const size_t length = (size_t)argc - 1U;

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
        const char *const argument = argv[index + 1U];
        char *end = NULL;

        errno = 0;
        const long value = strtol(argument, &end, 10);

        if (errno == ERANGE ||
            end == argument ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argument);
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

int main(int argc, char *argv[])
{
    return run(argc, argv);
}