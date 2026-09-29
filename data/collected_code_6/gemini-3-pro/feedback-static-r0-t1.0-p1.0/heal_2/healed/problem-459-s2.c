#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_uppercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    char *read_ptr = str;
    char *write_ptr = str;

    while (*read_ptr != '\0') {
        if (*read_ptr >= 'A' && *read_ptr <= 'Z') {
            read_ptr++;
        } else {
            *write_ptr = *read_ptr;
            write_ptr++;
            read_ptr++;
        }
    }
    *write_ptr = '\0';
}

int main(void) {
    char str1[] = "hello WORLD this IS a TEST string";
    
    remove_uppercase_substrings(str1);
    
    printf("%s\n", str1);
    
    return 0;
}