#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void increment_numeric_values(char *str, int k) {
    for (char *p = str; *p; p++) {
        if (*p >= '0' && *p <= '9') {
            *p = ((*p - '0' + k) % 10) + '0';
        }
    }
}

int main() {
    char *str1 = "abc123";
    char *str2 = "456def789";
    int k = 3;

    increment_numeric_values(str1, k);
    increment_numeric_values(str2, k);

    printf("Incremented str1: %s\n", str1);
    printf("Incremented str2: %s\n", str2);

    return 0;
}