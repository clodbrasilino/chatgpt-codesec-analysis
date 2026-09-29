#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int check_decimal_precision_2(const char *input) {
    regex_t regex;
    int ret;
    const char *pattern = "^[0-9]+\\.[0-9]{2}$";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    
    printf("Enter a decimal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (check_decimal_precision_2(input)) {
        printf("Valid decimal with precision 2\n");
    } else {
        printf("Invalid decimal\n");
    }
    
    return 0;
}