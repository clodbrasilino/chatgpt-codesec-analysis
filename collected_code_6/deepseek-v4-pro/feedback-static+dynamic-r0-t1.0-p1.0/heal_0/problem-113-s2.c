#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

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
        "123", "-123", "+123", "0", "-0", "+0",
        "12a", "a12", "", " ", "-", "+", "12 3",
        "2147483647", "-2147483648", "999999999999999999999",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("\"%s\" is %s\n", 
               test_strings[i],
               is_integer(test_strings[i]) ? "an integer" : "not an integer");
    }
    
    return 0;
}