#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

void left_rotate_string(char *str, size_t n, size_t max_len) {
    size_t len;
    char *temp;
    /* Possible weaknesses found:
     *  Unused variable: i [unusedVariable]
     */
    size_t i;
    
    if (str == NULL || max_len == 0) {
        return;
    }
    
    len = strnlen(str, max_len);
    
    if (len == 0 || n == 0) {
        return;
    }
    
    n = n % len;
    
    if (n == 0) {
        return;
    }
    
    temp = (char *)malloc(n);
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, n);
    memmove(str, str + n, len - n);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + (len - n), temp, n);
    
    free(temp);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    size_t rotate_by;
    int result;
    size_t len;
    int c;
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    len = strnlen(str, sizeof(str));
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else if (len == sizeof(str) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    printf("Enter number of positions to rotate left: ");
    result = scanf("%zu", &rotate_by);
    if (result != 1) {
        fprintf(stderr, "Invalid input for rotation count\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Original string: %s\n", str);
    
    left_rotate_string(str, rotate_by, sizeof(str));
    
    printf("Rotated string: %s\n", str);
    
    return 0;
}