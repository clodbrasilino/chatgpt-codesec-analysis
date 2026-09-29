#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIGITS 255

bool is_undulating(const char *num, size_t len) {
    if (len < 3) return false;
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)num[i])) return false;
    }
    
    if (num[0] == num[1]) return false;
    
    for (size_t i = 1; i < len - 1; i++) {
        if (num[i] == num[i-1] || num[i] == num[i+1]) {
            return false;
        }
        if (num[i-1] != num[i+1]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[BUFSIZ];
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else if (len == sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    if (len == 0 || len > MAX_DIGITS) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_undulating(input, len)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}