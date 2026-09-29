#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

char *remove_whitespaces(char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    char *read = str;
    char *write = str;
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!isspace((unsigned char)*read)) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            *write = *read;
            write++;
        }
        read++;
    }
    
    *write = '\0';
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