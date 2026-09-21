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
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    const char *read = str;
    size_t read_index = 0;
    char *write = str;
    size_t write_index = 0;
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read_index < len && *read != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!isspace((unsigned char)*read)) {
            if (write_index < len) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                *write++ = *read;
                write_index++;
            }
        }
        read++;
        read_index++;
    }
    
    if (write_index < len) {
        *write = '\0';
    } else if (len > 0) {
        str[len - 1] = '\0';
    }
    
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