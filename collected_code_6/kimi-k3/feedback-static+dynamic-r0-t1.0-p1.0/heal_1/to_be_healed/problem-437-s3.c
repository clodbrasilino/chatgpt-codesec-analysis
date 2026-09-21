#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t read_pos = 0;
    size_t write_pos = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    while (read_pos < len) {
        if (read_pos % 2 == 0) {
            str[write_pos] = str[read_pos];
            write_pos++;
        }
        read_pos++;
    }
    str[write_pos] = '\0';
}

int main(void) {
    char str[] = "Hello World";
    
    printf("Original: %s\n", str);
    remove_odd_chars(str);
    printf("Result: %s\n", str);
    
    return 0;
}