#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define ZODIAC_COUNT 12
#define INPUT_BUFFER_SIZE 64

static const char *chinese_zodiac(int year)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static const char *const signs[ZODIAC_COUNT] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    int index;

    index = year % ZODIAC_COUNT;
    if (index < 0) {
        index += ZODIAC_COUNT;
    }
    if (index < 0 || index >= ZODIAC_COUNT) {
        return "Unknown";
    }
    return signs[index];
}

static int parse_year(const char *text, int *out_year)
{
    char *endptr;
    long value;

    if (text == NULL || out_year == NULL) {
        return 0;
    }

    errno = 0;
    endptr = NULL;
    value = strtol(text, &endptr, 10);

    if (errno != 0 || endptr == text) {
        return 0;
    }

    while (*endptr == ' ' || *endptr == '\t' ||
           *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }

    if (*endptr != '\0') {
        return 0;
    }

    if (value < INT_MIN || value > INT_MAX) {
        return 0;
    }

    *out_year = (int)value;
    return 1;
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    len = strnlen(buffer, size);
    if (len == size - 1 && buffer[len - 1] != '\n') {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return 0;
    }

    return 1;
}

int main(int argc, char const *argv[])
{
    int year;

    if (argc > 1) {
        if (!parse_year(argv[1], &year)) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[INPUT_BUFFER_SIZE];

        memset(buffer, 0, sizeof(buffer));

        if (!read_line(buffer, sizeof(buffer))) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
        if (!parse_year(buffer, &year)) {
            fprintf(stderr, "Error: invalid input, expected an integer year.\n");
            return EXIT_FAILURE;
        }
    }

    printf("%s\n", chinese_zodiac(year));

    return EXIT_SUCCESS;
}