#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_number_at_end(const char *str, long *result) {
    if (str == NULL || result == NULL || *str == '\0') {
        return 0;
    }

    size_t str_len = 0;
    while (str[str_len] != '\0') {
        str_len++;
        if (str_len > 1024) {
            return 0;
        }
    }

    if (str_len == 0) {
        return 0;
    }

    const char *end = str + str_len - 1;

    while (end >= str && !isdigit((unsigned char)*end)) {
        end--;
    }

    if (end < str) {
        return 0;
    }

    const char *digit_end = end;
    while (end >= str && isdigit((unsigned char)*end)) {
        end--;
    }

    const char *digit_start = end + 1;
    size_t number_length = digit_end - digit_start + 1;

    if (number_length > 20) {
        return 0;
    }

    if (end >= str && !isspace((unsigned char)*end) && !ispunct((unsigned char)*end)) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char number_str[21];
    if (number_length >= sizeof(number_str)) {
        return 0;
    }

    if (number_length >= sizeof(number_str)) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(number_str, digit_start, number_length);
    number_str[number_length] = '\0';

    char *parsing_end = NULL;
    long parsed_value = strtol(number_str, &parsing_end, 10);

    if (parsing_end == NULL || *parsing_end != '\0') {
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

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
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