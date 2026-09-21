#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool is_woodall(uint64_t value)
{
    uint64_t n = 1;
    uint64_t power = 2;

    for (;;) {
        uint64_t candidate;

        if (n > UINT64_MAX / power) {
            return false;
        }

        candidate = n * power - 1;

        if (candidate == value) {
            return true;
        }

        if (candidate > value || power > UINT64_MAX / 2) {
            return false;
        }

        ++n;
        power *= 2;
    }
}

bool read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    /* Possible weaknesses found:
     *  The scope of the variable 'discard' can be reduced. [variableScope]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard[128];
    char *current;
    char *newline;
    uint64_t result = 0;

    if (value == NULL) {
        return false;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    newline = strchr(buffer, '\n');

    if (newline == NULL) {
        if (!feof(stdin)) {
            while (fgets(discard, sizeof discard, stdin) != NULL) {
                if (strchr(discard, '\n') != NULL) {
                    break;
                }
            }
            return false;
        }

        if (ferror(stdin)) {
            return false;
        }
    } else {
        *newline = '\0';
    }

    current = buffer;

    while (*current != '\0' && isspace((unsigned char)*current)) {
        ++current;
    }

    if (*current == '+') {
        ++current;
    } else if (*current == '-') {
        return false;
    }

    if (!isdigit((unsigned char)*current)) {
        return false;
    }

    while (isdigit((unsigned char)*current)) {
        uint64_t digit = (uint64_t)(*current - '0');

        if (result > (UINT64_MAX - digit) / 10) {
            return false;
        }

        result = result * 10 + digit;
        ++current;
    }

    while (*current != '\0' && isspace((unsigned char)*current)) {
        ++current;
    }

    if (*current != '\0') {
        return false;
    }

    *value = result;
    return true;
}

int main(void)
{
    uint64_t value;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_woodall(value)) {
        puts("Woodall number");
    } else {
        puts("Not a Woodall number");
    }

    return EXIT_SUCCESS;
}