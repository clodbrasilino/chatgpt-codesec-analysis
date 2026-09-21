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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t len;
    
    printf("Enter a decimal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else if (len == sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Input too long\n");
        return 1;
    }
    
    if (len == 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_valid_decimal_precision_2(input)) {
        printf("Valid decimal with precision up to 2\n");
    } else {
        printf("Invalid decimal or precision exceeds 2\n");
    }
    
    return 0;
}