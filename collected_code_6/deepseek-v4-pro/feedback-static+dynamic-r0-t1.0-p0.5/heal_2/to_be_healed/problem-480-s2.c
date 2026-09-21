#include <stdio.h>
#include <string.h>
#include <limits.h>

char max_occurring_char(const char *str) {
    if (str == NULL || *str == '\0') {
        return '\0';
    }
    
    int count[UCHAR_MAX + 1] = {0};
    const unsigned char *s = (const unsigned char *)str;
    
    while (*s) {
        count[*s]++;
        s++;
    }
    
    int max_count = 0;
    char max_char = '\0';
    
    for (int i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_char = (char)i;
        }
    }
    
    return max_char;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1000];
    
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
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    char result = max_occurring_char(str);
    
    if (result == '\0') {
        printf("Empty string\n");
    } else {
        printf("Maximum occurring character: %c\n", result);
    }
    
    return 0;
}