#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_numeric_values(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    int in_number = 0;
    
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            if (!in_number) {
                count++;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
        str++;
    }
    
    return count;
}

int main(void) {
    const char *test_strings[] = {
        "abc123def456",
        "no numbers here",
        "123",
        "",
        "1a2b3c4d5e",
        "123 456 789",
        "12.34 and 56",
        "abc",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("String: \"%s\"\n", test_strings[i]);
        printf("Numeric values: %d\n\n", count_numeric_values(test_strings[i]));
    }
    
    printf("Testing NULL string: %d\n", count_numeric_values(NULL));
    
    return 0;
}