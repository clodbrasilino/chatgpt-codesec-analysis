#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_first_and_last(char *str, size_t capacity, char target)
{
    char *first;
    char *last;
    size_t length;

    if (str == NULL || capacity == 0) {
        return -1;
    }

    length = strnlen(str, capacity);
    if (length == capacity) {
        return -1;
    }

    first = memchr(str, (unsigned char)target, length);
    if (first == NULL) {
        return 0;
    }

    last = first;
    for (char *p = first + 1; p < str + length; ++p) {
        if (*p == target) {
            last = p;
        }
    }

    if (first != last) {
        size_t last_offset = (size_t)(last - str);
        memmove(last, last + 1, length - last_offset);
        --length;
    }

    {
        size_t first_offset = (size_t)(first - str);
        memmove(first, first + 1, length - first_offset);
    }

    return first == last ? 1 : 2;
}

int main(void)
{
    enum { INPUT_CAPACITY = 1024, TARGET_CAPACITY = 3 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char target_input[TARGET_CAPACITY];
    size_t length;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = strnlen(input, sizeof input);
    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch != '\n') {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            }
            return EXIT_FAILURE;
        }
    }

    if (fgets(target_input, sizeof target_input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    length = strnlen(target_input, sizeof target_input);
    if (length == sizeof target_input || length == 0 ||
        target_input[0] == '\n') {
        return EXIT_FAILURE;
    }

    if (length == 1) {
        if (feof(stdin)) {
            return EXIT_FAILURE;
        }

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch != '\n') {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            }
            return EXIT_FAILURE;
        }
    } else if (target_input[1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        while (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        }
        return EXIT_FAILURE;
    }

    if (remove_first_and_last(input, sizeof input, target_input[0]) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", input) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}