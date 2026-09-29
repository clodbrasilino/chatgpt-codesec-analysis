#include <stdio.h>
#include <stdlib.h>

#define IPV4_TEXT_SIZE (sizeof("255.255.255.255"))

static int parse_octet(const char **cursor, unsigned int *octet)
{
    const char *current;
    unsigned int value = 0U;

    if (cursor == NULL || *cursor == NULL || octet == NULL) {
        return -1;
    }

    current = *cursor;

    if (*current < '0' || *current > '9') {
        return -1;
    }

    while (*current >= '0' && *current <= '9') {
        unsigned int digit = (unsigned int)(*current - '0');

        if (value > (255U - digit) / 10U) {
            return -1;
        }

        value = (value * 10U) + digit;
        ++current;
    }

    *cursor = current;
    *octet = value;

    return 0;
}

int remove_leading_zeroes(const char *input, char *output,
                          size_t output_size)
{
    const char *cursor;
    unsigned int first;
    unsigned int second;
    unsigned int third;
    unsigned int fourth;
    int written;

    if (input == NULL || output == NULL || output_size == 0U) {
        return -1;
    }

    cursor = input;

    if (parse_octet(&cursor, &first) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &second) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &third) != 0 || *cursor != '.') {
        return -1;
    }
    ++cursor;

    if (parse_octet(&cursor, &fourth) != 0 || *cursor != '\0') {
        return -1;
    }

    written = snprintf(output, output_size, "%u.%u.%u.%u",
                       first, second, third, fourth);

    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    char *normalized;
    int result = EXIT_FAILURE;

    if (argc != 2) {
        (void)fputs("Usage: program <IPv4 address>\n", stderr);
        return EXIT_FAILURE;
    }

    normalized = malloc(IPV4_TEXT_SIZE * sizeof(*normalized));
    if (normalized == NULL) {
        (void)fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (remove_leading_zeroes(argv[1], normalized, IPV4_TEXT_SIZE) != 0) {
        (void)fputs("Invalid IPv4 address\n", stderr);
    } else if (puts(normalized) != EOF) {
        result = EXIT_SUCCESS;
    }

    free(normalized);
    return result;
}