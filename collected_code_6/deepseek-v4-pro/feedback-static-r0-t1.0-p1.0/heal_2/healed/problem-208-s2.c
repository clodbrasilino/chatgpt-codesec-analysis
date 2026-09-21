#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_decimal_precision_2(const char *str) {
    regex_t regex;
    int ret;
    const char *pattern = "^[+-]?([0-9]+([.][0-9]{1,2})?|[.][0-9]{1,2})$";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t length;
    size_t len;
    
    printf("Enter a decimal number: ");
    length = getline(&input, &buffer_size, stdin);
    if (length == -1) {
        free(input);
        return 1;
    }
    
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
        length--;
    }
    
    if (length == 0 || input[0] == '\0') {
        printf("Invalid input\n");
        free(input);
        return 1;
    }
    
    if (is_valid_decimal_precision_2(input)) {
        printf("Valid decimal with precision up to 2\n");
    } else {
        printf("Invalid decimal or precision exceeds 2\n");
    }
    
    free(input);
    
    return 0;
}