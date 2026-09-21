#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

/* Possible weaknesses found:
 *  previous definition of 'get_zodiac_sign' with type 'const char *(int)'
 *  previous definition is here
 */
const char* get_zodiac_sign(int year) {
    const char* signs[] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    return signs[year % 12];
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || val < INT_MIN || val > INT_MAX || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid year format\n");
        return EXIT_FAILURE;
    }

    int year = (int)val;

    if (year < 0) {
        fprintf(stderr, "Invalid year provided\n");
        return EXIT_FAILURE;
    }

    size_t index = (size_t)year % 12;
    const char* sign = get_zodiac_sign(index);

    printf("%s\n", sign);

    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  conflicting types for 'get_zodiac_sign'
 *  conflicting types for 'get_zodiac_sign'; have 'const char *(size_t)' {aka 'const char *(long unsigned int)'}
 */
const char* get_zodiac_sign(size_t index) {
    const char* signs[] = {
        "Monkey", "Rooster", "Dog", "Pig",
        "Rat", "Ox", "Tiger", "Rabbit",
        "Dragon", "Snake", "Horse", "Goat"
    };
    if (index >= sizeof(signs) / sizeof(signs[0])) {
        return "Unknown";
    }
    return signs[index];
}