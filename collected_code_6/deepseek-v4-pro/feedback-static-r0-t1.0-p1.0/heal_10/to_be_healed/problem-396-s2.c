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
    size_t input_len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        len = input_len - 1;
    } else if (input_len == sizeof(input) - 1) {
        input[sizeof(input) - 1] = '\0';
        len = sizeof(input) - 1;
    } else {
        input[input_len] = '\0';
        len = input_len;
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