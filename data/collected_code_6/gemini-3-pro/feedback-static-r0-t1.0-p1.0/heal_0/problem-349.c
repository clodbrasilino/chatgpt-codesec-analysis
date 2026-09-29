#include <stdio.h>
#include <stdbool.h>

bool is_binary_string(const char *str) {
    if (str == NULL || *str == '\0') {
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
    const char *test_strings[] = {
        "101010",
        "102010",
        "",
        NULL,
        "00000000",
        "11111111",
        "101a10"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        bool result = is_binary_string(test_strings[i]);
        if (test_strings[i] != NULL) {
            printf("'%s' is ", test_strings[i]);
        } else {
            printf("NULL is ");
        }
        printf("%s\n", result ? "a binary string." : "NOT a binary string.");
    }

    return 0;
}