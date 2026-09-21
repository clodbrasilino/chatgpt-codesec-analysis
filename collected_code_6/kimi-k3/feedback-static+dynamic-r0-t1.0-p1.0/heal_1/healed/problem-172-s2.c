#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int count_std_occurrences(const char *str) {
    int count = 0;
    const char *ptr;
    
    if (str == NULL) {
        return -1;
    }
    
    ptr = str;
    while ((ptr = strstr(ptr, "std")) != NULL) {
        count++;
        ptr += 3;
    }
    
    return count;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t line_length;
    int result;
    
    printf("Enter a string: ");
    
    line_length = getline(&input, &input_size, stdin);
    if (line_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (line_length > 0 && input[line_length - 1] == '\n') {
        input[line_length - 1] = '\0';
    }
    
    result = count_std_occurrences(input);
    if (result < 0) {
        fprintf(stderr, "Error: Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    printf("Occurrences of 'std': %d\n", result);
    
    free(input);
    return EXIT_SUCCESS;
}