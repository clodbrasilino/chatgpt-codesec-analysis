#include <stdio.h>
#include <string.h>

char find_sum_character(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int sum = 0;
    while (*str != '\0') {
        sum += (unsigned char)(*str);
        str++;
    }

    return (char)(sum % 256);
}

int main() {
    const char *test_str = "abc";
    char result = find_sum_character(test_str);
    
    if (result != '\0') {
        printf("The sum character is: %c (ASCII: %d)\n", result, (unsigned char)result);
    } else {
        printf("Invalid input string.\n");
    }

    return 0;
}