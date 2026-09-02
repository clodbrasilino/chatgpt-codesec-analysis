#include <stdio.h>
#include <ctype.h>

int count_lowercase_letters(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str) {
        if (islower((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    const char *test_string = "Hello World! abcDEF";
    int result = count_lowercase_letters(test_string);
    printf("Lowercase letters count: %d\n", result);
    return 0;
}