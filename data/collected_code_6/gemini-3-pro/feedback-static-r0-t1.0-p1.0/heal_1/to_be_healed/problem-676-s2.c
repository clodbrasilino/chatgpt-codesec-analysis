#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

void filter_alphanumeric(const char *input, char *output) {
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret) {
        output[0] = '\0';
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t in_len = strlen(input);
    size_t out_idx = 0;
    
    for (size_t i = 0; i < in_len; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp[2] = {input[i], '\0'};
        ret = regexec(&regex, temp, 0, NULL, 0);
        if (ret == REG_NOMATCH) {
            output[out_idx++] = input[i];
        }
    }
    
    output[out_idx] = '\0';
    regfree(&regex);
}

int main(void) {
    const char *input_str = "Hello, World! 123 @#Test";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *output_str = malloc(strlen(input_str) + 1);
    
    if (!output_str) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    filter_alphanumeric(input_str, output_str);
    
    printf("Original: %s\n", input_str);
    printf("Filtered: %s\n", output_str);
    
    free(output_str);
    
    return 0;
}