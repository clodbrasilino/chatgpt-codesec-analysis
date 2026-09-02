#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool is_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    const char *p = str;
    
    if (*p == '+' || *p == '-') {
        p++;
    }
    
    if (*p == '\0') {
        return false;
    }
    
    while (*p != '\0') {
        if (!isdigit((unsigned char)*p)) {
            return false;
        }
        p++;
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "123",
        "-456",
        "+789",
        "12a4",
        "",
        "+",
        "-",
        "12 34",
        "0",
        "-0",
        "2147483647",
        "-2147483648",
        "3.14",
        "12\n"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("\"%s\" -> %s\n", 
               test_strings[i], 
               is_integer(test_strings[i]) ? "integer" : "not integer");
    }
    
    return 0;
}