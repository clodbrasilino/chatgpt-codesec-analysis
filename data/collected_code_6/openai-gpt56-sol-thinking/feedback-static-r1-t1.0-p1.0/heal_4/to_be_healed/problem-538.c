#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_size(size_t *total, size_t amount)
{
    if (total == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (amount > SIZE_MAX - *total) {
        errno = EOVERFLOW;
        return -1;
    }

    *total += amount;
    return 0;
}

static size_t escaped_character_length(unsigned char character)
{
    switch (character) {
        case '"':
        case '\\':
        case '\n':
        case '\r':
        case '\t':
        case '\b':
        case '\f':
            return 2;
        default:
            return (character < 0x20 || character == 0x7f) ? 4 : 1;
    }
}

static char hexadecimal_digit(unsigned int value)
{
    return (char)(value < 10U ? '0' + value : 'a' + value - 10U);
}

static char *append_escaped_string(char *destination, const char *source)
{
    while (*source != '\0') {
        unsigned char character = (unsigned char)*source++;

        switch (character) {
            case '"':
                *destination++ = '\\';
                *destination++ = '"';
                break;
            case '\\':
                *destination++ = '\\';
                *destination++ = '\\';
                break;
            case '\n':
                *destination++ = '\\';
                *destination++ = 'n';
                break;
            case '\r':
                *destination++ = '\\';
                *destination++ = 'r';
                break;
            case '\t':
                *destination++ = '\\';
                *destination++ = 't';
                break;
            case '\b':
                *destination++ = '\\';
                *destination++ = 'b';
                break;
            case '\f':
                *destination++ = '\\';
                *destination++ = 'f';
                break;
            default:
                if (character < 0x20 || character == 0x7f) {
                    *destination++ = '\\';
                    *destination++ = 'x';
                    *destination++ = hexadecimal_digit(character >> 4);
                    *destination++ = hexadecimal_digit(character & 0x0fU);
                } else {
                    *destination++ = (char)character;
                }
                break;
        }
    }

    return destination;
}

static char *string_list_to_tuple(char *const *list, size_t count)
{
    size_t required_size = 3;
    char *tuple;
    char *position;

    if (count != 0 && list == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        const unsigned char *current;

        if (list[i] == NULL) {
            errno = EINVAL;
            return NULL;
        }

        if (i != 0 && add_size(&required_size, 2) != 0) {
            return NULL;
        }

        if (add_size(&required_size, 2) != 0) {
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        current = (const unsigned char *)list[i];

        while (*current != '\0') {
            if (add_size(&required_size,
                         escaped_character_length(*current)) != 0) {
                return NULL;
            }

            ++current;
        }
    }

    if (count == 1 && add_size(&required_size, 1) != 0) {
        return NULL;
    }

    tuple = malloc(required_size);
    if (tuple == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    position = tuple;
    *position++ = '(';

    for (size_t i = 0; i < count; ++i) {
        if (i != 0) {
            *position++ = ',';
            *position++ = ' ';
        }

        *position++ = '"';
        position = append_escaped_string(position, list[i]);
        *position++ = '"';
    }

    if (count == 1) {
        *position++ = ',';
    }

    *position++ = ')';
    *position = '\0';

    return tuple;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    size_t count = argc > 1 ? (size_t)(argc - 1) : 0;
    char *tuple = string_list_to_tuple(
        count == 0 ? NULL : argv + 1,
        count
    );

    if (tuple == NULL) {
        perror("string_list_to_tuple");
        return EXIT_FAILURE;
    }

    errno = 0;

    if (fputs(tuple, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        int saved_errno = errno;

        if (saved_errno == 0) {
            saved_errno = EIO;
        }

        free(tuple);
        errno = saved_errno;
        perror("output");
        return EXIT_FAILURE;
    }

    free(tuple);
    return EXIT_SUCCESS;
}