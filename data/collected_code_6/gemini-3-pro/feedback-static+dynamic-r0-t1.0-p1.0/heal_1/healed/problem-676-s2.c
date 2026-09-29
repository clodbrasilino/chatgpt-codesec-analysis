#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 4096

void filter_alphanumeric(const char *input, char *output, size_t max_len) {
    if (!input || !output || max_len == 0) {
        if (output) output[0] = '\0';
        return;
    }

    size_t in_len = strnlen(input, max_len);
    size_t out_idx = 0;
    
    for (size_t i = 0; i < in_len; i++) {
        if (isalnum((unsigned char)input[i])) {
            output[out_idx++] = input[i];
        }
    }
    
    output[out_idx] = '\0';
}

int main(void) {
    const char *input_str = "Hello, World! 123 @#Test";
    
    size_t input_len = strnlen(input_str, MAX_BUFFER_SIZE);
    
    char *output_str = malloc(input_len + 1);
    
    if (!output_str) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    filter_alphanumeric(input_str, output_str, input_len);
    
    printf("Original: %s\n", input_str);
    printf("Filtered: %s\n", output_str);
    
    free(output_str);
    
    return 0;
}