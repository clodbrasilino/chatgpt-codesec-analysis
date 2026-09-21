#include <stdio.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int min_flips_to_alternate(const char *str, size_t max_len) {
    size_t len = safe_strlen(str, max_len);
    if (len == 0) return 0;
    
    int flips_start0 = 0;
    int flips_start1 = 0;
    
    for (size_t i = 0; i < len; i++) {
        char expected_bit = (i % 2 == 0) ? '0' : '1';
        if (str[i] != expected_bit) {
            flips_start0++;
        }
        
        expected_bit = (i % 2 == 0) ? '1' : '0';
        if (str[i] != expected_bit) {
            flips_start1++;
        }
    }
    
    return (flips_start0 < flips_start1) ? flips_start0 : flips_start1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[101];
    
    printf("Enter binary string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[sizeof(input) - 1] = '\0';
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        printf("Minimum flips required: %d\n", min_flips_to_alternate(input, sizeof(input)));
    }
    
    return 0;
}