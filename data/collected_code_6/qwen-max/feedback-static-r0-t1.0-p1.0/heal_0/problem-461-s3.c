#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_uppercase(const char *str) {
    int count = 0;
    while (*str) {
        if (isupper((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    const char *test_str = "Hello World!";
    int uppercase_count = count_uppercase(test_str);
    printf("Number of uppercase letters: %d\n", uppercase_count);
    return 0;
}