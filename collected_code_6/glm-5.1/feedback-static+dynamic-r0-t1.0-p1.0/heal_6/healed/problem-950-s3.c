#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

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

int main(int argc, char *argv[]) {
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