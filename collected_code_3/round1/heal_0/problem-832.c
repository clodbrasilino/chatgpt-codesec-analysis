#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int extract_max_value(const char *str) {
    int max = 0, num = 0;
    while (*str) {
        if (isdigit(*str)) {
            num = num * 10 + (*str - '0');
        } else {
            if (num > max) {
                max = num;
            }
            num = 0;
        }
        str++;
    }
    if (num > max) {
        max = num;
    }
    return max;
}

int main() {
    char str[] = "abc123def456ghi789";
    int max = extract_max_value(str);
    printf("The maximum numeric value in the string is %d\n", max);
    return 0;
}