#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_armstrong(uintmax_t number)
{
    uintmax_t value = number;
    uintmax_t sum = 0;
    unsigned int digits = 0;

    do {
        ++digits;
        value /= 10;
    } while (value != 0);

    value = number;

    do {
        uintmax_t digit = value % 10;
        uintmax_t power = 1;

        for (unsigned int i = 0; i < digits; ++i) {
            if (digit != 0 && power > number / digit) {
                return false;
            }
            power *= digit;
        }

        if (sum > number || power > number - sum) {
            return false;
        }

        sum += power;
        value /= 10;
    } while (value != 0);

    return sum == number;
}

static bool read_number(uintmax_t *number)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[256];

    if (number == NULL) {
        return false;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        return false;
    }

    size_t length = 0;
    while (line[length] != '\0' && line[length] != '\n') {
        ++length;
    }

    if (line[length] == '\n') {
        line[length] = '\0';
    } else if (line[length] == '\0' && !feof(stdin)) {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return false;
    }

    char *start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return false;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *number = value;
    return true;
}

int main(void)
{
    uintmax_t number;

    if (!read_number(&number)) {
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX " is %san Armstrong number.\n",
           number, is_armstrong(number) ? "" : "not ");

    return EXIT_SUCCESS;
}