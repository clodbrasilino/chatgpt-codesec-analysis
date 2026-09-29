#include <stdio.h>
#include <ctype.h>

int count_upper_case(const char *str) {
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
    int upper_count = count_upper_case(test_string);
    printf("Number of uppercase characters: %d\n", upper_count);
    return 0;
}