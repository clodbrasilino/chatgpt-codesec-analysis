#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void left_rotate_string(char *str, size_t n) {
    size_t len;
    char *temp;
    size_t i;
    
    if (str == NULL) {
        return;
    }
    
    len = strnlen(str, 100);
    if (len == 0 || len == 100) {
        return;
    }
    
    if (n == 0) {
        return;
    }
    
    n = n % len;
    
    if (n == 0) {
        return;
    }
    
    temp = (char *)malloc(n * sizeof(char));
    if (temp == NULL) {
        return;
    }
    
    for (i = 0; i < n; i++) {
        temp[i] = str[i];
    }
    
    for (i = 0; i < len - n; i++) {
        str[i] = str[i + n];
    }
    
    for (i = 0; i < n; i++) {
        str[len - n + i] = temp[i];
    }
    
    free(temp);
    temp = NULL;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[101];
    size_t rotate_by;
    int result;
    int c;
    size_t len;
    
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
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                break;
            }
        }
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    
    printf("Enter number of positions to rotate left: ");
    result = scanf("%zu", &rotate_by);
    if (result != 1) {
        fprintf(stderr, "Invalid input for rotation count\n");
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == EOF) {
                break;
            }
        }
        return 1;
    }
    
    printf("Original string: %s\n", str);
    
    left_rotate_string(str, rotate_by);
    
    printf("Rotated string: %s\n", str);
    
    return 0;
}