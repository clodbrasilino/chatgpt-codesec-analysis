#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

enum { IPV4_STRING_SIZE = sizeof "255.255.255.255" };

static int normalize_ipv4(const char *input, char **output)
{
    const char *cursor;
    char *normalized;
    size_t used = 0;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    normalized = malloc(IPV4_STRING_SIZE);
    if (normalized == NULL) {
        return -1;
    }

    cursor = input;

    for (unsigned int octet_index = 0; octet_index < 4; ++octet_index) {
        char *end;
        unsigned long value;
        int written;
        size_t remaining;

        if (*cursor < '0' || *cursor > '9') {
            free(normalized);
            return -1;
        }

        errno = 0;
        value = strtoul(cursor, &end, 10);

        if (errno == ERANGE || end == cursor || value > 255UL) {
            free(normalized);
            return -1;
        }

        if ((octet_index < 3 && *end != '.') ||
            (octet_index == 3 && *end != '\0')) {
            free(normalized);
            return -1;
        }

        remaining = IPV4_STRING_SIZE - used;

        /* Possible weaknesses found:
         * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
         */
        written = snprintf(
            normalized + used,
            remaining,
            octet_index == 0 ? "%lu" : ".%lu",
            value
        );

        if (written < 0 || (size_t)written >= remaining) {
            free(normalized);
            return -1;
        }

        used += (size_t)written;
        cursor = octet_index < 3 ? end + 1 : end;
    }

    *output = normalized;
    return 0;
}

int main(int argc, char *argv[])
{
    char *normalized = NULL;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <IPv4-address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (normalize_ipv4(argv[1], &normalized) != 0) {
        fputs("Invalid IPv4 address\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(normalized) == EOF) {
        free(normalized);
        return EXIT_FAILURE;
    }

    free(normalized);
    return EXIT_SUCCESS;
}