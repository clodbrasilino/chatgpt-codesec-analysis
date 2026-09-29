#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char replacement) {
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        if (*str == ' ') {
            *str = replacement;
        }
        str++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    char replacement;
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    str[strcspn(str, "\n")] = '\0';
    
    printf("Enter replacement character: ");
    if (scanf(" %c", &replacement) != 1) {
        return 1;
    }
    
    replace_spaces(str, replacement);
    
    printf("Modified string: %s\n", str);
    
    return 0;
}