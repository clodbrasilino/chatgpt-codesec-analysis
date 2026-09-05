#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int find_max_difference(const char *binary_string) {
    if (binary_string == NULL) {
        return -1;
    }
    
    size_t length = strlen(binary_string);
    if (length == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (binary_string[i] != '0' && binary_string[i] != '1') {
            return -1;
        }
    }
    
    int max_diff = INT_MIN;
    int current_sum = 0;
    
    for (size_t i = 0; i < length; i++) {
        int value = (binary_string[i] == '0') ? 1 : -1;
        current_sum += value;
        
        if (current_sum > max_diff) {
            max_diff = current_sum;
        }
        
        if (current_sum < 0) {
            current_sum = 0;
        }
    }
    
    return max_diff;
}

int main(void) {
    const char *test_strings[] = {
        "11000010001",
        "111111",
        "000000",
        "101010",
        "1100",
        NULL
    };
    
    for (size_t i = 0; test_strings[i] != NULL; i++) {
        int result = find_max_difference(test_strings[i]);
        if (result >= 0) {
            printf("String: %s, Max difference: %d\n", test_strings[i], result);
        } else {
            printf("String: %s, Error: Invalid input\n", test_strings[i]);
        }
    }
    
    return EXIT_SUCCESS;
}