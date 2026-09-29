#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    int ones_count = 0;
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '1') {
            ones_count++;
        }
    }
    
    return ones_count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *s = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    
    for (size_t i = 0; i < len; ++i) {
        if (s[i] != '0' && s[i] != '1') {
            fprintf(stderr, "Error: Input must be a binary string\n");
            return EXIT_FAILURE;
        }
    }
    
    int result = count_odd_rotations(s);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}