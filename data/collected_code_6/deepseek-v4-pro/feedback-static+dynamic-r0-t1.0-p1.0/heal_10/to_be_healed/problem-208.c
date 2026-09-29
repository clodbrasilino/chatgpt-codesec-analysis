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
    
    if (input[0] == '\0') {
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
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ssize_t read;
    size_t max_size = 255;
    size_t input_len;
    int has_newline;
    
    printf("Enter a decimal number: ");
    errno = 0;
    read = getline(&input, &len, stdin);
    
    if (read == -1) {
        free(input);
        return 1;
    }
    
    if (read == 0) {
        free(input);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > (ssize_t)(max_size + 1)) {
        free(input);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    has_newline = (read > 0 && input[read - 1] == '\n');
    
    if (has_newline) {
        input[read - 1] = '\0';
        input_len = (size_t)(read - 1);
    } else {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        input[read] = '\0';
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        input_len = (size_t)read;
    }
    
    if (input_len > max_size) {
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