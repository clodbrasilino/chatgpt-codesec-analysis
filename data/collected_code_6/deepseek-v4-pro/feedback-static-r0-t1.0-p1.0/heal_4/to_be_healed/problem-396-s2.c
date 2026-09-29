#include <stdio.h>
#include <string.h>

int starts_ends_same(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strnlen(str, 1024);
    if (len == 0 || len >= 1024) {
        return 0;
    }
    
    return str[0] == str[len - 1];
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256] = {0};
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    if (input[0] == '\0') {
        return 1;
    }
    
    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    }
    
    if (starts_ends_same(input)) {
        printf("The string starts and ends with the same character.\n");
    } else {
        printf("The string does not start and end with the same character.\n");
    }
    
    return 0;
}