#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *remove_whitespaces(char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t write_pos = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (!isspace((unsigned char)str[i])) {
            str[write_pos] = str[i];
            write_pos++;
        }
    }
    
    str[write_pos] = '\0';
    return str;
}

int main(void) {
    char str1[] = "  Hello   World  ";
    printf("Original: \"%s\"\n", str1);
    remove_whitespaces(str1);
    printf("Modified: \"%s\"\n", str1);
    
    char str2[] = "\tTab\tand\nNewline\r\n";
    printf("Original: \"%s\"\n", str2);
    remove_whitespaces(str2);
    printf("Modified: \"%s\"\n", str2);
    
    char str3[] = "NoWhitespace";
    printf("Original: \"%s\"\n", str3);
    remove_whitespaces(str3);
    printf("Modified: \"%s\"\n", str3);
    
    return 0;
}