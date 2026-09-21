#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char *decimal_to_octal(int decimal) {
    size_t buffer_size = 13;
    char *octal = malloc(buffer_size * sizeof(char));
    if (octal == NULL) {
        return NULL;
    }
    
    if (decimal == 0) {
        if (buffer_size < 2) {
            free(octal);
            return NULL;
        }
        octal[0] = '0';
        octal[1] = '\0';
        return octal;
    }
    
    int is_negative = 0;
    unsigned int num;
    if (decimal < 0) {
        is_negative = 1;
        num = (unsigned int)(-(long)decimal);
    } else {
        num = (unsigned int)decimal;
    }
    
    size_t temp_size = 12;
    char *temp = malloc(temp_size * sizeof(char));
    if (temp == NULL) {
        free(octal);
        return NULL;
    }
    
    size_t i = 0;
    while (num > 0 && i < temp_size) {
        temp[i++] = '0' + (num % 8);
        num /= 8;
    }
    
    size_t index = 0;
    if (is_negative) {
        if (index < buffer_size - 1) {
            octal[index++] = '-';
        }
    }
    
    size_t j = i;
    while (j > 0 && index < buffer_size - 1) {
        j--;
        octal[index++] = temp[j];
    }
    
    if (index < buffer_size) {
        octal[index] = '\0';
    } else {
        octal[buffer_size - 1] = '\0';
    }
    
    free(temp);
    return octal;
}

int main(void) {
    int test_values[] = {0, 8, 64, -8, -64, 123, -123, 100, -100, INT_MIN, INT_MAX};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        char *result = decimal_to_octal(test_values[i]);
        if (result != NULL) {
            printf("Decimal: %d -> Octal: %s\n", test_values[i], result);
            free(result);
        } else {
            printf("Memory allocation failed for decimal: %d\n", test_values[i]);
        }
    }
    
    return 0;
}