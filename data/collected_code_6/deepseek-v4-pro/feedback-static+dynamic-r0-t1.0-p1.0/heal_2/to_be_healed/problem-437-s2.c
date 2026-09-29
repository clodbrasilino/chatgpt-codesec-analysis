#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str) {
    if (str == NULL) {
        return;
    }

    int i, j = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    
    for (i = 0; i < len; i++) {
        if (i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(void) {
    char str1[] = "abcdefgh";
    char str2[] = "hello world";
    char str3[] = "a";
    char str4[] = "";
    
    printf("Original: %s\n", str1);
    remove_odd_chars(str1);
    printf("Modified: %s\n\n", str1);
    
    printf("Original: %s\n", str2);
    remove_odd_chars(str2);
    printf("Modified: %s\n\n", str2);
    
    printf("Original: %s\n", str3);
    remove_odd_chars(str3);
    printf("Modified: %s\n\n", str3);
    
    printf("Original: %s\n", str4);
    remove_odd_chars(str4);
    printf("Modified: %s\n", str4);
    
    return 0;
}