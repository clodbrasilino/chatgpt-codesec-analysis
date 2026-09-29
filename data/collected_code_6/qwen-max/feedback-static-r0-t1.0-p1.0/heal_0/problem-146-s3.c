#include <stdio.h>
#include <string.h>

int ascii_value_sum(const char *str) {
    int sum = 0;
    while (*str != '\0') {
        sum += (unsigned char)*str++;
    }
    return sum;
}

int main() {
    const char *test_string = "Hello, World!";
    int result = ascii_value_sum(test_string);
    printf("The ASCII value sum of the characters in the string is: %d\n", result);
    return 0;
}