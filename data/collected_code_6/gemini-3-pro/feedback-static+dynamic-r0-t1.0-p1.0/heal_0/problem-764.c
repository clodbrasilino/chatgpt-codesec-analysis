#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

size_t count_numeric_values(const char *str) {
    size_t count = 0;
    
    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isdigit((unsigned char)*str)) {
            count++;
        }
        str++;
    }

    return count;
}

int main(void) {
    const char *test_str = "abc123def45gh6";
    size_t numeric_count;

    numeric_count = count_numeric_values(test_str);
    printf("%zu\n", numeric_count);

    return 0;
}