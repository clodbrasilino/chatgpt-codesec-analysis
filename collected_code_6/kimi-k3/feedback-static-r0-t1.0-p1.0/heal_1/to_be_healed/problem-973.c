#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t n) {
    size_t len;
    char *temp;
    size_t i;
    
    if (str == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    
    if (len == 0 || n == 0) {
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
    char str[100];
    size_t rotate_by;
    int result;
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    
    printf("Enter number of positions to rotate left: ");
    result = scanf("%zu", &rotate_by);
    if (result != 1) {
        fprintf(stderr, "Invalid input for rotation count\n");
        return 1;
    }
    
    printf("Original string: %s\n", str);
    
    left_rotate_string(str, rotate_by);
    
    printf("Rotated string: %s\n", str);
    
    return 0;
}