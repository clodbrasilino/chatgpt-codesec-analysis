#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LENGTH ((size_t)100000)

static int minimum_swaps(const char *first, const char *second,
                         size_t length, size_t *result)
{
    size_t zero_one = 0;
    size_t one_zero = 0;

    if (first == NULL || second == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return 0;
        }

        if (first[i] == '0' && second[i] == '1') {
            ++zero_one;
        } else if (first[i] == '1' && second[i] == '0') {
            ++one_zero;
        }
    }

    if ((zero_one % 2) != (one_zero % 2)) {
        return 0;
    }

    *result = zero_one / 2 + one_zero / 2;

    if ((zero_one % 2) != 0) {
        *result += 2;
    }

    return 1;
}

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int read_binary_string(char *buffer, size_t capacity, size_t *length)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_LENGTH + 3];
    size_t used = 0;
    int ch;

    if (buffer == NULL || length == NULL ||
        capacity < 2 || capacity > MAX_LENGTH + 1) {
        return 0;
    }

    buffer[0] = '\0';
    *length = 0;

    do {
        if (fgets(input, sizeof input, stdin) == NULL) {
            return 0;
        }

        used = 0;
        while (is_space_char((unsigned char)input[used])) {
            ++used;
        }
    } while (input[used] == '\0');

    size_t output_length = 0;

    for (;;) {
        while (input[used] != '\0' &&
               !is_space_char((unsigned char)input[used])) {
            if (input[used] != '0' && input[used] != '1') {
                return 0;
            }

            if (output_length >= capacity - 1) {
                return 0;
            }

            buffer[output_length++] = input[used++];
        }

        if (input[used] != '\0') {
            break;
        }

        if (output_length >= capacity - 1) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
            if (ch != EOF && !is_space_char(ch)) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                while ((ch = fgetc(stdin)) != EOF && !is_space_char(ch)) {
                }
                return 0;
            }
            break;
        }

        if (fgets(input, sizeof input, stdin) == NULL) {
            break;
        }

        used = 0;
    }

    if (output_length == 0) {
        return 0;
    }

    buffer[output_length] = '\0';
    *length = output_length;
    return 1;
}

int main(void)
{
    const size_t capacity = MAX_LENGTH + 1;
    char *first = malloc(capacity);
    char *second = malloc(capacity);
    size_t first_length = 0;
    size_t second_length = 0;
    size_t swaps = 0;
    int status = EXIT_SUCCESS;

    if (first == NULL || second == NULL) {
        fputs("Memory allocation failed\n", stderr);
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!read_binary_string(first, capacity, &first_length) ||
        !read_binary_string(second, capacity, &second_length)) {
        fputs("Invalid input\n", stderr);
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (first_length != second_length ||
        !minimum_swaps(first, second, first_length, &swaps)) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

cleanup:
    free(second);
    free(first);
    return status;
}