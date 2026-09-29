#include <stdio.h>
#include <stdlib.h>

struct ipv4_address {
    unsigned int octet[4];
};

static int parse_octet(const char **const cursor,
                       unsigned int *const octet)
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
        const unsigned int digit = (unsigned int)(*current - '0');

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

static int parse_ipv4(const char *const input,
                      struct ipv4_address *const address)
{
    const char *cursor;
    size_t index;

    if (input == NULL || address == NULL) {
        return -1;
    }

    cursor = input;

    for (index = 0U; index < 4U; ++index) {
        if (parse_octet(&cursor, &address->octet[index]) != 0) {
            return -1;
        }

        if (index < 3U) {
            if (*cursor != '.') {
                return -1;
            }
            ++cursor;
        }
    }

    return *cursor == '\0' ? 0 : -1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    struct ipv4_address address;

    if (argc != 2) {
        (void)fputs("Usage: program <IPv4 address>\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_ipv4(argv[1], &address) != 0) {
        (void)fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u.%u.%u.%u\n",
               address.octet[0],
               address.octet[1],
               address.octet[2],
               address.octet[3]) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}