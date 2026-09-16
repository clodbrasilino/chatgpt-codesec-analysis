#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int count_numeric(const char *str) {
    int count = 0;
    bool in_number = false;

    while (*str) {
        if (isdigit((unsigned char)*str)) {
            if (!in_number) {
                count++;
                in_number = true;
            }
        } else {
            in_number = false;
        }
        str++;
    }

    return count;
}

int main() {
    const char *test_str = "There are 123 numbers, like 45 and 678, but not 9a.";
    int result = count_numeric(test_str);
    printf("Count of numeric values: %d\n", result);
    return 0;
}