#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void move_numbers_to_string(const char *input, char *output, size_t output_size) {
    size_t i, j = 0;
    
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }
    
    for (i = 0; input[i] != '\0' && j < output_size - 1; i++) {
        if (isdigit((unsigned char)input[i])) {
            output[j++] = input[i];
        }
    }
    
    output[j] = '\0';
}

int main(void) {
    const char *test_string = "abc123def456ghi789";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[64];
    
    move_numbers_to_string(test_string, result, sizeof(result));
    printf("Original string: %s\n", test_string);
    printf("Numbers extracted: %s\n", result);
    
    return 0;
}