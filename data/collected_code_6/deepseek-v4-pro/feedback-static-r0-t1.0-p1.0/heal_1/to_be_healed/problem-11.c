#include <stdio.h>
#include <string.h>

void remove_first_last(char *str, char ch) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    
    int first = -1;
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            first = i;
            break;
        }
    }
    
    if (first == -1) {
        return;
    }
    
    int last = -1;
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ch) {
            last = i;
            break;
        }
    }
    
    int write = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (int read = 0; read < len; read++) {
        if (read == first || read == last) {
            continue;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        str[write++] = str[read];
    }
    str[write] = '\0';
}

int main(void) {
    char str1[] = "hello world";
    remove_first_last(str1, 'o');
    printf("%s\n", str1);
    
    char str2[] = "a";
    remove_first_last(str2, 'a');
    printf("%s\n", str2);
    
    char str3[] = "aaa";
    remove_first_last(str3, 'a');
    printf("%s\n", str3);
    
    char str4[] = "programming";
    remove_first_last(str4, 'g');
    printf("%s\n", str4);
    
    char str5[] = "test";
    remove_first_last(str5, 'x');
    printf("%s\n", str5);
    
    return 0;
}