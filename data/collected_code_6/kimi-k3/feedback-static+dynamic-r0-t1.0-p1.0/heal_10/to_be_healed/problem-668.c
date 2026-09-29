#include <stdio.h>
#include <string.h>
#include <stddef.h>

void replaceMultipleOccurrences(char *str, char ch, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    
    size_t read = 0;
    size_t write = 0;
    size_t len = strnlen(str, size);
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < len && str[read] != '\0') {
        /* Possible weaknesses found:
         *  Assuming that condition 'write>=size-1' is not redundant
         */
        if (write >= size - 1) {
            break;
        }
        
        /* Possible weaknesses found:
         *  Condition 'write<size' is always true [knownConditionTrueFalse]
         *  Condition 'write<size' is always true
         */
        if (write < size) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            str[write++] = str[read];
        }
        
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (str[read] == ch) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (read < len && str[read] == ch) {
                read++;
            }
        } else {
            read++;
        }
    }
    
    if (write < size) {
        str[write] = '\0';
    }
}

int main(void) {
    char str1[] = "aaabbbcccdddaaa";
    char str2[] = "hello world";
    char str3[] = "aaaa";
    char str4[] = "no duplicates";
    
    printf("Before: %s\n", str1);
    replaceMultipleOccurrences(str1, 'a', sizeof(str1));
    printf("After:  %s\n\n", str1);
    
    printf("Before: %s\n", str2);
    replaceMultipleOccurrences(str2, 'l', sizeof(str2));
    printf("After:  %s\n\n", str2);
    
    printf("Before: %s\n", str3);
    replaceMultipleOccurrences(str3, 'a', sizeof(str3));
    printf("After:  %s\n\n", str3);
    
    printf("Before: %s\n", str4);
    replaceMultipleOccurrences(str4, 'x', sizeof(str4));
    printf("After:  %s\n", str4);
    
    return 0;
}