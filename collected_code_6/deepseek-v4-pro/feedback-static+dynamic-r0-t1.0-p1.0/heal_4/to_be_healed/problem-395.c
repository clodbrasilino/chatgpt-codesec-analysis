#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 256
#define INPUT_BUFFER_SIZE 1024

char find_first_non_repeated_char(const char *str) {
    int count[TABLE_SIZE] = {0};
    
    if (str == NULL) {
        return '\0';
    }
    
    const char *ptr = str;
    while (*ptr != '\0') {
        count[(unsigned char)*ptr]++;
        ptr++;
    }
    
    ptr = str;
    while (*ptr != '\0') {
        if (count[(unsigned char)*ptr] == 1) {
            return *ptr;
        }
        ptr++;
    }
    
    return '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("No non-repeated character found\n");
        return EXIT_SUCCESS;
    }
    
    char result = find_first_non_repeated_char(input);
    
    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found\n");
    }
    
    return EXIT_SUCCESS;
}