#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_numbers_and_positions(const char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)str[i])) {
            printf("Number: %c, Position: %zu\n", str[i], i);
        }
    }
}

int main(void) {
    const char *test_string = "a1b23c4";
    
    print_numbers_and_positions(test_string);
    
    return 0;
}