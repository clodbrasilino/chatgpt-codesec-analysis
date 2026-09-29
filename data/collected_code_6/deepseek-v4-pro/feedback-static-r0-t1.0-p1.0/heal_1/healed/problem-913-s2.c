#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_number_at_end(const char *str, long *result) {
    if (str == NULL || result == NULL || *str == '\0') {
        return 0;
    }

    size_t len = strnlen(str, 4096);
    if (len == 0 || str[len - 1] == '\0' && len < 4096) {
        if (len == 0) return 0;
    }
    if (len >= 4096 && str[len - 1] != '\0') {
        return 0;
    }

    const char *end = str + len - 1;
    char number_buffer[64];
    size_t number_length = 0;

    while (end >= str && isdigit((unsigned char)*end)) {
        if (number_length >= sizeof(number_buffer) - 1) {
            return 0;
        }
        number_buffer[number_length++] = *end;
        end--;
    }

    if (number_length == 0) {
        return 0;
    }

    if (end >= str && !isspace((unsigned char)*end) && !ispunct((unsigned char)*end)) {
        return 0;
    }

    char reversed[64];
    if (number_length >= sizeof(reversed)) {
        return 0;
    }

    size_t i;
    for (i = 0; i < number_length; i++) {
        reversed[i] = number_buffer[number_length - 1 - i];
    }
    reversed[number_length] = '\0';

    char *parsing_end = NULL;
    long parsed_value = strtol(reversed, &parsing_end, 10);
    
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