#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int minRotations(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    if (n == 0) {
        return 0;
    }
    
    size_t temp_size = 2 * n + 1;
    char *temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, n);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp + n, str, n);
    temp[2 * n] = '\0';
    
    for (size_t i = 1; i <= n; i++) {
        if (memcmp(str, temp + i, n) == 0) {
            free(temp);
            return (int)i;
        }
    }
    
    free(temp);
    return (int)n;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[101];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("Empty string\n");
        return 0;
    }
    
    if (len > 100) {
        printf("Input too long\n");
        return 1;
    }
    
    int rotations = minRotations(str);
    if (rotations == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("%d\n", rotations);
    
    return 0;
}