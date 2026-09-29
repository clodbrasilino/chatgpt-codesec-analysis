#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool has_number_at_end(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return false;
    }

    const char *p = str;
    while (*(p + 1) != '\0') {
        p++;
    }

    return isdigit((unsigned char)*p) != 0;
}

int main(void) {
    const char *test_strings[] = {
        "hello123",
        "world",
        "test ",
        "12345",
        "",
        NULL
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            bool result = has_number_at_end(test_strings[i]);
            printf("String: \"%s\" -> Ends with number: %s\n", 
                   test_strings[i], result ? "true" : "false");
        } else {
            bool result = has_number_at_end(test_strings[i]);
            printf("String: NULL -> Ends with number: %s\n", 
                   result ? "true" : "false");
        }
    }

    return 0;
}