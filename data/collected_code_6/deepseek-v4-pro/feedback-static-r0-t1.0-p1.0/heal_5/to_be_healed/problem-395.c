#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 256

char find_first_non_repeated_char(const char *str) {
    int count[TABLE_SIZE] = {0};
    size_t i;
    
    if (str == NULL) {
        return '\0';
    }
    
    if (str[0] == '\0') {
        return '\0';
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        count[(unsigned char)str[i]]++;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
    }
    
    return '\0';
}

int main(void) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t char_read;
    char result;
    /* Possible weaknesses found:
     *  Unused variable: len [unusedVariable]
     */
    size_t len;
    
    printf("Enter a string: ");
    char_read = getline(&input, &bufsize, stdin);
    if (char_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (char_read > 0 && input[char_read - 1] == '\n') {
        input[char_read - 1] = '\0';
    }
    
    result = find_first_non_repeated_char(input);
    
    if (result != '\0') {
        printf("First non-repeated character: %c\n", result);
    } else {
        printf("No non-repeated character found\n");
    }
    
    free(input);
    return EXIT_SUCCESS;
}