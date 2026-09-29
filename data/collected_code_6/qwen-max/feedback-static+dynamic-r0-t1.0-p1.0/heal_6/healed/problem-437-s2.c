#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str, size_t len) {
    char *write = str;
    for (size_t i = 0; i < len; i++) {
        if ((str[i] >= '0' && str[i] <= '9' && (str[i] - '0') % 2 == 0) || str[i] < '0' || str[i] > '9') {
            *write++ = str[i];
        }
    }
    *write = '\0';
}

int main() {
    char str[] = "1234567890";
    remove_odd_chars(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}