#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_substrings(const char *str) {
    int count = 0;
    int freq[256] = {0};
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        freq[(unsigned char)str[i]]++;
    }
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            count += freq[i] * (freq[i] + 1) / 2;
        }
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t line_length;
    
    printf("Enter a string: ");
    line_length = getline(&input, &input_size, stdin);
    if (line_length == -1) {
        free(input);
        return 1;
    }
    
    if (line_length > 0 && input[line_length - 1] == '\n') {
        input[line_length - 1] = '\0';
    }
    
    int result = count_substrings(input);
    printf("Number of substrings: %d\n", result);
    
    free(input);
    return 0;
}