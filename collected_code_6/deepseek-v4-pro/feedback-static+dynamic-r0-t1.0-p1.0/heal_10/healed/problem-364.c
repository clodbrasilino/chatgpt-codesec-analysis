#include <stdio.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int min_flips_to_alternate(const char *str, size_t len) {
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
    char input[101] = {0};
    
    printf("Enter binary string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strcspn(input, "\n");
        if (len < sizeof(input)) {
            input[len] = '\0';
        } else {
            input[sizeof(input) - 1] = '\0';
            len = sizeof(input) - 1;
        }
        
        size_t str_len = safe_strlen(input, sizeof(input));
        if (str_len >= sizeof(input)) {
            str_len = sizeof(input) - 1;
        }
        
        int valid = 1;
        for (size_t i = 0; i < str_len; i++) {
            if (input[i] != '0' && input[i] != '1') {
                valid = 0;
                break;
            }
        }
        
        if (valid) {
            printf("Minimum flips required: %d\n", min_flips_to_alternate(input, str_len));
        } else {
            printf("Invalid input: string must contain only '0' and '1' characters\n");
        }
    }
    
    return 0;
}