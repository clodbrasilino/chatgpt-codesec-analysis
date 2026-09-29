#include <stdio.h>
#include <string.h>

void remove_char(char *str, char ch) {
    if (str == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *write = str;
    const char *read = str;
    size_t read_index = 0;
    
    while (read_index < len) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read[read_index] != ch) {
            size_t write_offset = (size_t)(write - str);
            if (write_offset >= len) {
                break;
            }
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            write[write_offset] = read[read_index];
            write++;
        }
        read_index++;
    }
    
    size_t write_offset = (size_t)(write - str);
    if (write_offset <= len) {
        write[write_offset] = '\0';
    }
}

int main(void) {
    char str1[] = "hello world";
    char str2[] = "mississippi";
    char str3[] = "aaaaaa";
    char str4[] = "";
    
    remove_char(str1, 'o');
    printf("Removing 'o' from \"hello world\": %s\n", str1);
    
    remove_char(str2, 's');
    printf("Removing 's' from \"mississippi\": %s\n", str2);
    
    remove_char(str3, 'a');
    printf("Removing 'a' from \"aaaaaa\": %s\n", str3);
    
    remove_char(str4, 'x');
    printf("Removing 'x' from \"\": %s\n", str4);
    
    return 0;
}