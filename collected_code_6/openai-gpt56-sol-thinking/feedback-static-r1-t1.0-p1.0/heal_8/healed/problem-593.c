#include <stdio.h>
#include <stdlib.h>

enum {
    IPV4_OCTET_COUNT = 4,
    IPV4_OCTET_MAX = 255
};

struct ipv4_address {
    unsigned int octet[IPV4_OCTET_COUNT];
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

        if (value > (IPV4_OCTET_MAX - digit) / 10U) {
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
    struct ipv4_address parsed = {{0U, 0U, 0U, 0U}};
    const char *cursor;
    unsigned int index;

    if (input == NULL || address == NULL) {
        return -1;
    }

    cursor = input;

    for (index = 0U; index < IPV4_OCTET_COUNT; ++index) {
        if (parse_octet(&cursor, &parsed.octet[index]) != 0) {
            return -1;
        }

        if (index + 1U < IPV4_OCTET_COUNT) {
            if (*cursor != '.') {
                return -1;
            }

            ++cursor;
        }
    }

    if (*cursor != '\0') {
        return -1;
    }

    *address = parsed;
    return 0;
}

int main(int argc, char **const argv)
{
    struct ipv4_address address;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
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