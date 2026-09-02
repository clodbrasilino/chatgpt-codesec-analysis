#include <stdio.h>
#include <ctype.h>

int count_uppercase(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str) {
        if (isupper((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    const char *test_string = "Hello World! This is a TEST String.";
    int uppercase_count = count_uppercase(test_string);
    printf("Uppercase characters: %d\n", uppercase_count);
    return 0;
}