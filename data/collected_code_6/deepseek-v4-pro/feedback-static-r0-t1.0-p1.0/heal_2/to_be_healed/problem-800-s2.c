#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

char *remove_whitespaces(char *str)
{
    if (str == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  Variable 'read' can be declared as pointer to const [constVariablePointer]
     */
    char *read = str;
    char *write = str;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i = 0;
    
    while (i < len) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!isspace((unsigned char)read[i])) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            *write++ = read[i];
        }
        i++;
    }
    
    *write = '\0';
    
    return str;
}

int main(void)
{
    char str1[] = "Hello World from C";
    char str2[] = "  leading and trailing  ";
    char str3[] = "\tTab\nNewline\rCarriage";
    char str4[] = "NoWhitespaces";
    char str5[] = "";
    
    printf("Original: '%s'\n", str1);
    remove_whitespaces(str1);
    printf("Modified: '%s'\n\n", str1);
    
    printf("Original: '%s'\n", str2);
    remove_whitespaces(str2);
    printf("Modified: '%s'\n\n", str2);
    
    printf("Original: '\\tTab\\nNewline\\rCarriage'\n");
    remove_whitespaces(str3);
    printf("Modified: '%s'\n\n", str3);
    
    printf("Original: '%s'\n", str4);
    remove_whitespaces(str4);
    printf("Modified: '%s'\n\n", str4);
    
    printf("Original: '%s'\n", str5);
    remove_whitespaces(str5);
    printf("Modified: '%s'\n", str5);
    
    return 0;
}