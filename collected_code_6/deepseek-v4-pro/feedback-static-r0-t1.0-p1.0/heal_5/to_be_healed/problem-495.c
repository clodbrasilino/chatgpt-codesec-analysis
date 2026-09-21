#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_lowercase_substrings(const char *input, char *output, size_t output_size) {
    if (input == NULL || output == NULL || output_size == 0) {
        return;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    
    if (ret != 0) {
        output[0] = '\0';
        return;
    }

    size_t in_pos = 0;
    size_t out_pos = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    regmatch_t match;

    while (in_pos < input_len && out_pos < output_size - 1) {
        ret = regexec(&regex, input + in_pos, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            size_t remaining = input_len - in_pos;
            size_t available = output_size - out_pos - 1;
            size_t copy_len = remaining < available ? remaining : available;
            if (copy_len > 0 && out_pos + copy_len <= output_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(output + out_pos, input + in_pos, copy_len);
                out_pos += copy_len;
            }
            break;
        } else if (ret == 0) {
            size_t match_start = match.rm_so;
            if (match_start > 0) {
                size_t available = output_size - out_pos - 1;
                size_t copy_len = match_start < available ? match_start : available;
                if (copy_len > 0 && out_pos + copy_len <= output_size) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(output + out_pos, input + in_pos, copy_len);
                    out_pos += copy_len;
                }
            }
            size_t match_len = match.rm_eo;
            if (match_len == 0) {
                match_len = 1;
            }
            if (in_pos + match_len > input_len) {
                break;
            }
            in_pos += match_len;
        } else {
            break;
        }
    }

    output[out_pos] = '\0';
    regfree(&regex);
}

int main(void) {
    const char *test_str = "HelloWorld123abcDEFxyz456";
    char *result = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t result_size = strlen(test_str) + 1;

    result = (char *)malloc(result_size);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    remove_lowercase_substrings(test_str, result, result_size);
    printf("Original: %s\n", test_str);
    printf("Result: %s\n", result);

    free(result);
    return 0;
}