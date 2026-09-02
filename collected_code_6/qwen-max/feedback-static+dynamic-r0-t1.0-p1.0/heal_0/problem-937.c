#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int count_max_char(const char *str, char *max_char) {
    int count_arr[UCHAR_MAX + 1] = {0};
    int max_count = 0;

    while (*str) {
        if (isprint(*str)) {
            count_arr[(unsigned char)*str]++;
            if (count_arr[(unsigned char)*str] > max_count) {
                max_count = count_arr[(unsigned char)*str];
                *max_char = *str;
            }
        }
        str++;
    }

    return max_count;
}

int main() {
    const char *input = "example string with many characters";
    char max_char;
    int max_count = count_max_char(input, &max_char);
    if (max_count > 0) {
        printf("Max character: '%c' with count: %d\n", max_char, max_count);
    } else {
        printf("No printable characters found.\n");
    }
    return 0;
}