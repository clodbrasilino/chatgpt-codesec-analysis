#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool starts_with_number(const char *str, int num) {
    if (str == NULL) {
        return false;
    }
    
    char num_str[12];
    int len = snprintf(num_str, sizeof(num_str), "%d", num);
    
    if (len < 0 || (size_t)len >= sizeof(num_str)) {
        return false;
    }
    
    return strncmp(str, num_str, (size_t)len) == 0;
}

int main(void) {
    const char *str = "123Hello";
    int num = 123;

    if (starts_with_number(str, num)) {
        printf("The string starts with %d\n", num);
    } else {
        printf("The string does not start with %d\n", num);
    }

    return 0;
}