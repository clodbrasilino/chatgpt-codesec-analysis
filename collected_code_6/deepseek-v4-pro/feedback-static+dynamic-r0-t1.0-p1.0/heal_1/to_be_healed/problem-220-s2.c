#include <stdio.h>
#include <string.h>

void replace_chars(char *str, int n) {
    int count = 0;
    char *p = str;
    
    while (*p && count < n) {
        if (*p == ' ' || *p == ',' || *p == '.') {
            *p = ':';
            count++;
        }
        p++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    int n;
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    str[strcspn(str, "\n")] = '\0';
    
    printf("Enter maximum replacements: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    
    replace_chars(str, n);
    printf("Result: %s\n", str);
    
    return 0;
}