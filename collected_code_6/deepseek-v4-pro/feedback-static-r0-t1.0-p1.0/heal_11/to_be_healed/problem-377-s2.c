#include <stdio.h>
#include <string.h>

void remove_char(char *str, size_t size, char ch) {
    if (str == NULL || size == 0) {
        return;
    }
    
    char *write = str;
    const char *read = str;
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     *  outer condition: (unsigned long)(read-str)<size
     */
    while ((size_t)(read - str) < size && *read != '\0') {
        /* Possible weaknesses found:
         *  opposite inner condition: (unsigned long)(read-str)>=size
         *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
         */
        if ((size_t)(read - str) >= size) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (*read != ch) {
            if ((size_t)(write - str) >= size) {
                break;
            }
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            *write = *read;
            write++;
        }
        read++;
    }
    
    if ((size_t)(write - str) < size) {
        *write = '\0';
    } else {
        str[size - 1] = '\0';
    }
}

int main(void) {
    char str1[] = "hello world";
    char str2[] = "mississippi";
    char str3[] = "aaaaaa";
    char str4[] = "";
    
    remove_char(str1, sizeof(str1), 'o');
    printf("Removing 'o' from \"hello world\": %s\n", str1);
    
    remove_char(str2, sizeof(str2), 's');
    printf("Removing 's' from \"mississippi\": %s\n", str2);
    
    remove_char(str3, sizeof(str3), 'a');
    printf("Removing 'a' from \"aaaaaa\": %s\n", str3);
    
    remove_char(str4, sizeof(str4), 'x');
    printf("Removing 'x' from \"\": %s\n", str4);
    
    return 0;
}