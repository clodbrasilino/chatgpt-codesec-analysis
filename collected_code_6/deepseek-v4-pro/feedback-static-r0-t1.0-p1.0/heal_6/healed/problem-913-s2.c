#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int get_number_at_end(const char *str, long *result) {
    if (str == NULL || result == NULL || *str == '\0') {
        return 0;
    }

    size_t len = strnlen(str, 64);
    if (len == 0 || len >= 64) {
        return 0;
    }

    const char *end = str + len - 1;

    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }

    if (end < str) {
        return 0;
    }

    const char *digit_end = end;
    while (digit_end >= str && isdigit((unsigned char)*digit_end)) {
        digit_end--;
    }

    if (digit_end == end) {
        return 0;
    }

    if (digit_end >= str && !isspace((unsigned char)*digit_end) && !ispunct((unsigned char)*digit_end)) {
        return 0;
    }

    const char *digit_start = digit_end + 1;
    size_t number_length = end - digit_start + 1;

    char number_buffer[64];
    if (number_length >= sizeof(number_buffer)) {
        return 0;
    }

    memcpy(number_buffer, digit_start, number_length);
    number_buffer[number_length] = '\0';

    errno = 0;
    char *parsing_end = NULL;
    long parsed_value = strtol(number_buffer, &parsing_end, 10);

    if (errno == ERANGE || parsing_end == NULL || *parsing_end != '\0') {
        return 0;
    }

    *result = parsed_value;
    return 1;
}

int main(void) {
    const char *test_strings[] = {
        "hello123",
        "test456",
        "no_number_here",
        "abc",
        "",
        "1234",
        "trailing789",
        "number000",
        "space123 ",
        "123abc",
        "verylongnumber123456789012345678901234567890",
        "end42"
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    for (size_t i = 0; i < num_tests; i++) {
        long value = 0;
        int success = get_number_at_end(test_strings[i], &value);
        
        if (success) {
            printf("'%s' -> number: %ld\n", test_strings[i], value);
        } else {
            printf("'%s' -> no valid number at end\n", test_strings[i]);
        }
    }

    return 0;
}