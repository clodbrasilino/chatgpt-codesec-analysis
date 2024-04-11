#include <stdio.h>
#include <ctype.h>

int count_lowercase(const char *str) {
    int count = 0;
    while (*str) {
        if (islower(*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    char str[] = "Hello World!";
    printf("Number of lowercase letters: %d\n", count_lowercase(str));
    return 0;
}