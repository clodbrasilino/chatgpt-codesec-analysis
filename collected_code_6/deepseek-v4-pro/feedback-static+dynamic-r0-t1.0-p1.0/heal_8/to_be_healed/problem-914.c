#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_alternating(const char *str) {
    if (str == NULL || str[0] == '\0' || str[1] == '\0') {
        return false;
    }
    
    char first = str[0];
    char second = str[1];
    
    if (first == second) {
        return false;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            if (str[i] != first) {
                return false;
            }
        } else {
            if (str[i] != second) {
                return false;
            }
        }
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    if (is_alternating(buffer)) {
        printf("The string consists of two alternating characters.\n");
    } else {
        printf("The string does not consist of two alternating characters.\n");
    }
    
    return 0;
}