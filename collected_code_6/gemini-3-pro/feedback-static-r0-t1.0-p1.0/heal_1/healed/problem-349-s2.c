#include <stdio.h>
#include <stdbool.h>

bool is_binary_string(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (*str == '\0') {
        return false; 
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return false;
        }
        str++;
    }

    return true;
}

int main(void) {
    const char *bool_str[] = {"false", "true"};
    
    const char *test1 = "10101011";
    const char *test2 = "101210";
    const char *test3 = "";
    const char *test4 = NULL;

    printf("'%s' is binary: %s\n", test1, bool_str[is_binary_string(test1)]);
    printf("'%s' is binary: %s\n", test2, bool_str[is_binary_string(test2)]);
    printf("'%s' is binary: %s\n", test3, bool_str[is_binary_string(test3)]);
    printf("NULL is binary: %s\n", bool_str[is_binary_string(test4)]);

    return 0;
}