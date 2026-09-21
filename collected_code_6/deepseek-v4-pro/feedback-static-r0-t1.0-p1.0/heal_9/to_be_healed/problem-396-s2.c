#include <stdio.h>
#include <string.h>

int starts_ends_same(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return 0;
    }
    return str[0] == str[len - 1];
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    len = strcspn(input, "\n");
    if (len < sizeof(input)) {
        input[len] = '\0';
    } else {
        input[sizeof(input) - 1] = '\0';
        len = sizeof(input) - 1;
    }
    
    if (len == 0) {
        return 1;
    }
    
    if (starts_ends_same(input, len)) {
        printf("The string starts and ends with the same character.\n");
    } else {
        printf("The string does not start and end with the same character.\n");
    }
    
    return 0;
}