#include <stdio.h>
#include <ctype.h>

int count_numeric(const char *str) {
    int count = 0;
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    const char *test_string = "a1b2c3d4e5f6g7h8i9j0";
    int result = count_numeric(test_string);
    printf("Number of numeric values: %d\n", result);
    return 0;
}