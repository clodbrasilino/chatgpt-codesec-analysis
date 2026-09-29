#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool starts_with_number(const char *str, int num) {
    char num_str[20];
    snprintf(num_str, sizeof(num_str), "%d", num);
    return strncmp(str, num_str, strlen(num_str)) == 0;
}

int main() {
    const char *str = "123Hello";
    int num = 123;

    if (starts_with_number(str, num)) {
        printf("The string starts with %d\n", num);
    } else {
        printf("The string does not start with %d\n", num);
    }

    return 0;
}