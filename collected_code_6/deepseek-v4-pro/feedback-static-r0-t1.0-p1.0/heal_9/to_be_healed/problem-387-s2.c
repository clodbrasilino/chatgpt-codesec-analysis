#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static bool is_hex_even(const char *hex_str) {
    size_t len;
    
    if (hex_str == NULL || *hex_str == '\0') {
        return false;
    }
    
    len = 0;
    while (len < 32 && hex_str[len] != '\0') {
        if (!isxdigit((unsigned char)hex_str[len])) {
            return false;
        }
        len++;
    }
    
    if (len == 0) {
        return false;
    }
    
    switch (hex_str[len - 1]) {
        case '0': case '2': case '4': case '6': case '8':
        case 'A': case 'C': case 'E':
        case 'a': case 'c': case 'e':
            return true;
        case '1': case '3': case '5': case '7': case '9':
        case 'B': case 'D': case 'F':
        case 'b': case 'd': case 'f':
            return false;
        default:
            return false;
    }
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t input_len;
    size_t i;
    int c;
    
    input_len = getline(&input, &bufsize, stdin);
    if (input_len == -1) {
        free(input);
        printf("Odd\n");
        return 0;
    }
    
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len == 0 || input_len > 32) {
        free(input);
        printf("Odd\n");
        return 0;
    }
    
    for (i = 0; i < (size_t)input_len; i++) {
        if (!isxdigit((unsigned char)input[i])) {
            free(input);
            printf("Odd\n");
            return 0;
        }
    }
    
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    c = fgetc(stdin);
    /* Possible weaknesses found:
     *  outer condition: c!=EOF
     */
    if (c != '\n' && c != EOF) {
        /* Possible weaknesses found:
         *  identical inner condition: c!=EOF
         *  Identical inner 'if' condition is always true. [identicalInnerCondition]
         */
        if (c != EOF) {
            ungetc(c, stdin);
        }
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = fgetc(stdin)) != '\n' && c != EOF) {
            if (c == EOF) break;
        }
        free(input);
        printf("Odd\n");
        return 0;
    }
    
    if (is_hex_even(input)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    
    free(input);
    return 0;
}