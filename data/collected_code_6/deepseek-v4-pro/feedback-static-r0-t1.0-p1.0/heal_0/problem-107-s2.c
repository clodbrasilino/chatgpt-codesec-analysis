#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int is_hex_number(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        if (str[2] == '\0') {
            return 0;
        }
        for (int i = 2; str[i] != '\0'; i++) {
            if (!isxdigit((unsigned char)str[i])) {
                return 0;
            }
        }
        return 1;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isxdigit((unsigned char)str[i])) {
            return 0;
        }
    }
    
    return 1;
}

int count_hex_numbers_in_range(const char *start, const char *end) {
    if (start == NULL || end == NULL) {
        return -1;
    }
    
    char *start_copy = strdup(start);
    char *end_copy = strdup(end);
    
    if (start_copy == NULL || end_copy == NULL) {
        free(start_copy);
        free(end_copy);
        return -1;
    }
    
    unsigned long start_val = strtoul(start_copy, NULL, 16);
    unsigned long end_val = strtoul(end_copy, NULL, 16);
    
    free(start_copy);
    free(end_copy);
    
    if (start_val > end_val) {
        return 0;
    }
    
    unsigned long count = end_val - start_val + 1;
    
    if (count > INT_MAX) {
        return INT_MAX;
    }
    
    return (int)count;
}

int main(void) {
    const char *test_start = "0x1A";
    const char *test_end = "0x2F";
    
    int result = count_hex_numbers_in_range(test_start, test_end);
    
    if (result >= 0) {
        printf("Number of hex values in range [%s, %s]: %d\n", 
               test_start, test_end, result);
    } else {
        printf("Error: Invalid input parameters\n");
    }
    
    printf("Is '0x1A' a hex number? %s\n", 
           is_hex_number("0x1A") ? "yes" : "no");
    printf("Is '1A' a hex number? %s\n", 
           is_hex_number("1A") ? "yes" : "no");
    printf("Is '0x' a hex number? %s\n", 
           is_hex_number("0x") ? "yes" : "no");
    printf("Is 'G1' a hex number? %s\n", 
           is_hex_number("G1") ? "yes" : "no");
    
    return 0;
}