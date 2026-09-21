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
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    size_t max_size = 255;
    
    printf("Enter a decimal number: ");
    read = getline(&input, &len, stdin);
    if (read == -1) {
        free(input);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && (size_t)read <= max_size + 1) {
        if (input[read - 1] == '\n') {
            input[read - 1] = '\0';
            read--;
        }
    } else {
        free(input);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read < 0 || (size_t)read > max_size) {
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