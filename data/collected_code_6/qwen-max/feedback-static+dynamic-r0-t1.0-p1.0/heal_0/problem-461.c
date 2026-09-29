#include <stdio.h>
#include <ctype.h>

int count_uppercase(const char *str) {
    int count = 0;
    while (*str) {
        if (isupper(*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    const char *input = "Hello, World!";
    int uppercase_count = count_uppercase(input);
    printf("Number of uppercase letters: %d\n", uppercase_count);
    return 0;
}