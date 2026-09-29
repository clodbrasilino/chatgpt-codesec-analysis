#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str != NULL) {
        while (len < max_len && str[len] != '\0') {
            len++;
        }
    }
    return len;
}

static void safe_memcpy(char *dest, size_t dest_size, size_t dest_offset, const char *src, size_t src_len) {
    if (dest == NULL || src == NULL) {
        return;
    }
    
    if (dest_offset + src_len > dest_size) {
        return;
    }
    
    for (size_t i = 0; i < src_len; i++) {
        dest[dest_offset + i] = src[i];
    }
}

void int_to_roman(int num, char *result, size_t result_size) {
    if (result == NULL || result_size == 0) {
        return;
    }

    if (num <= 0 || num > 3999) {
        result[0] = '\0';
        return;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char symbols[][3] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    result[0] = '\0';
    int remaining = num;
    size_t current_len = 0;
    
    for (int i = 0; i < 13; i++) {
        while (remaining >= values[i]) {
            size_t symbol_len = safe_strlen(symbols[i], sizeof(symbols[i]));
            
            if (current_len + symbol_len + 1 <= result_size) {
                safe_memcpy(result, result_size, current_len, symbols[i], symbol_len);
                current_len += symbol_len;
                result[current_len] = '\0';
            } else {
                return;
            }
            remaining -= values[i];
        }
    }
}

int main(void) {
    int test_numbers[] = {1, 3, 4, 9, 58, 1994, 3999};
    int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    char *roman = NULL;
    size_t roman_size = 32;
    
    roman = (char *)calloc(roman_size, sizeof(char));
    if (roman == NULL) {
        return 1;
    }
    
    for (int i = 0; i < num_tests; i++) {
        memset(roman, 0, roman_size);
        int_to_roman(test_numbers[i], roman, roman_size);
        printf("%d = %s\n", test_numbers[i], roman);
    }
    
    free(roman);
    return 0;
}