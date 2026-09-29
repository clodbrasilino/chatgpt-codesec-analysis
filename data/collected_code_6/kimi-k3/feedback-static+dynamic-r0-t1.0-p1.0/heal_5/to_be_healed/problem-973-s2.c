#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t positions) {
    if (str == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }
    
    positions = positions % len;
    if (positions == 0) {
        return;
    }
    
    char *temp = (char *)malloc(positions);
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, positions);
    
    memmove(str, str + positions, len - positions);
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str + len - positions, temp, positions);
    
    free(temp);
    temp = NULL;
}

int main(void) {
    char str1[] = "HelloWorld";
    char str2[] = "Programming";
    char str3[] = "A";
    char str4[] = "";
    
    printf("Original: %s\n", str1);
    left_rotate_string(str1, 3);
    printf("Rotated by 3: %s\n\n", str1);
    
    printf("Original: %s\n", str2);
    left_rotate_string(str2, 5);
    printf("Rotated by 5: %s\n\n", str2);
    
    printf("Original: %s\n", str3);
    left_rotate_string(str3, 1);
    printf("Rotated by 1: %s\n\n", str3);
    
    printf("Original: %s\n", str4);
    left_rotate_string(str4, 2);
    printf("Rotated by 2: %s\n\n", str4);
    
    char str5[] = "TestString";
    printf("Original: %s\n", str5);
    left_rotate_string(str5, 15);
    printf("Rotated by 15: %s\n", str5);
    
    return 0;
}