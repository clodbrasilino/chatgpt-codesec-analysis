#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

int check_decimal_precision_2(const char *input) {
    regex_t regex;
    int ret;
    const char *pattern = "^[0-9]+\\.[0-9]{2}$";
    
    if (input == NULL) {
        return 0;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t nread;
    
    printf("Enter a decimal number: ");
    errno = 0;
    nread = getline(&input, &len, stdin);
    
    if (nread == -1) {
        free(input);
        return 1;
    }
    
    if (nread > 0 && input[nread - 1] == '\n') {
        input[nread - 1] = '\0';
        nread--;
    }
    
    if (nread <= 0) {
        free(input);
        return 1;
    }
    
    if (nread > 255) {
        free(input);
        return 1;
    }
    
    if (input[nread] != '\0') {
        free(input);
        return 1;
    }
    
    if (check_decimal_precision_2(input)) {
        printf("Valid decimal with precision 2\n");
    } else {
        printf("Invalid decimal\n");
    }
    
    free(input);
    return 0;
}