#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

bool is_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    if (*str == '-' || *str == '+') {
        str++;
    }
    
    if (*str == '\0') {
        return false;
    }
    
    while (*str != '\0') {
        if (!isdigit((unsigned char)*str)) {
            return false;
        }
        str++;
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "123",
        "-456",
        "+789",
        "0",
        "12.34",
        "abc",
        "12a",
        "",
        "-",
        "+",
        NULL,
        " 123",
        "123 ",
        "-2147483648",
        "2147483647",
        "2147483648",
        "-2147483649"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] == NULL) {
            printf("NULL: %s\n", is_integer(test_strings[i]) ? "true" : "false");
        } else {
            printf("\"%s\": %s\n", test_strings[i], is_integer(test_strings[i]) ? "true" : "false");
        }
    }
    
    return 0;
}