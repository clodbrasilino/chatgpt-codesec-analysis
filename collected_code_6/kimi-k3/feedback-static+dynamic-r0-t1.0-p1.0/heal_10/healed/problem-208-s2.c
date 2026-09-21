#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 256

int validate_decimal_precision(const char *input) {
    regex_t regex;
    int ret;
    int result = 0;
    
    if (input == NULL) {
        return 0;
    }
    
    ret = regcomp(&regex, "^[+-]?[0-9]+\\.[0-9]{2}$", REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, input, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret != REG_NOMATCH) {
        result = 0;
    }
    
    regfree(&regex);
    return result;
}

int main(void) {
    char input[MAX_INPUT_SIZE + 2];
    size_t len;
    int c;
    int too_long = 0;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(input, sizeof(input));
    
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }
    
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        too_long = 1;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }
    
    if (len >= MAX_INPUT_SIZE) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (validate_decimal_precision(input)) {
        printf("Valid: %s\n", input);
        return EXIT_SUCCESS;
    } else {
        printf("Invalid: %s\n", input);
        return EXIT_FAILURE;
    }
}