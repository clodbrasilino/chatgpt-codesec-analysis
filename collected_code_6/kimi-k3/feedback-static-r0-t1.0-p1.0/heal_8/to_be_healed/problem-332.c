#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

#define CHARSET_SIZE (UCHAR_MAX + 1)
#define INPUT_SIZE 1024

void countCharFrequency(const char *str, unsigned long frequency[], size_t freq_size)
{
    size_t i;
    if (str == NULL || frequency == NULL || freq_size < CHARSET_SIZE) {
        return;
    }
    for (i = 0; str[i] != '\0'; i++) {
        frequency[(unsigned char)str[i]]++;
    }
}

int main(void)
{
    unsigned long frequency[CHARSET_SIZE] = {0};
    char *input = NULL;
    size_t input_capacity = INPUT_SIZE;
    size_t input_len = 0;
    int c;
    int i;
    
    input = (char *)malloc(input_capacity);
    if (input == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (input_len >= input_capacity - 1) {
            size_t new_capacity;
            char *new_input;
            
            if (input_capacity > SIZE_MAX / 2) {
                free(input);
                return 1;
            }
            
            new_capacity = input_capacity * 2;
            
            if (new_capacity < input_capacity || new_capacity > SIZE_MAX) {
                free(input);
                return 1;
            }
            
            new_input = (char *)realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }
            input = new_input;
            input_capacity = new_capacity;
        }
        input[input_len++] = (char)c;
    }
    
    if (ferror(stdin)) {
        free(input);
        return 1;
    }
    
    input[input_len] = '\0';
    
    countCharFrequency(input, frequency, CHARSET_SIZE);
    
    for (i = 0; i < CHARSET_SIZE; i++) {
        if (frequency[i] > 0) {
            if (i >= 32 && i <= 126) {
                printf("'%c': %lu\n", i, frequency[i]);
            } else {
                printf("0x%02x: %lu\n", i, frequency[i]);
            }
        }
    }
    
    free(input);
    return 0;
}