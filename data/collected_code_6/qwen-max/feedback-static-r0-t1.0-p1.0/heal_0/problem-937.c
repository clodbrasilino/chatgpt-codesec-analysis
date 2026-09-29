#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

char find_most_common_char(const char *str) {
    int counts[256] = {0};
    int max = 0;
    char result = '\0';
    while (*str) {
        counts[(unsigned char)*str]++;
        if (counts[(unsigned char)*str] > max) {
            max = counts[(unsigned char)*str];
            result = *str;
        }
        str++;
    }
    return result;
}

int main() {
    const char *input = "example string with text";
    char most_common = find_most_common_char(input);
    printf("The most common character is: '%c'\n", most_common);
    return 0;
}