#include <stdio.h>
#include <stdbool.h>

bool is_binary_string(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    while (*str) {
        if (*str != '0' && *str != '1') {
            return false;
        }
        str++;
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "101010",
        "110011",
        "0",
        "1",
        "100102",
        "",
        "abc",
        "1010 0101",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        if (is_binary_string(test_strings[i])) {
            printf("\"%s\" is a binary string\n", test_strings[i]);
        } else {
            printf("\"%s\" is not a binary string\n", test_strings[i]);
        }
    }
    
    return 0;
}