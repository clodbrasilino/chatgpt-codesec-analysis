#include <stdio.h>
#include <string.h>

void remove_even_chars(char *str) {
    if (str == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int write_index = 0;
    
    for (int i = 1; i < len; i += 2) {
        str[write_index++] = str[i];
    }
    
    str[write_index] = '\0';
}

int main(void) {
    char str1[] = "abcdefgh";
    char str2[] = "hello world";
    char str3[] = "a";
    char str4[] = "";
    
    remove_even_chars(str1);
    remove_even_chars(str2);
    remove_even_chars(str3);
    remove_even_chars(str4);
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    
    return 0;
}