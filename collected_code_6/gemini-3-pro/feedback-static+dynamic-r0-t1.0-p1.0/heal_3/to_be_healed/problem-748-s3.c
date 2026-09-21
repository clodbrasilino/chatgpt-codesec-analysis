#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces_regex(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t length = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'length<1000000' is redundant or the array 'input[27]' is accessed at index 999999, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'length<1000000' is not redundant
     */
    while (length < 1000000 && input[length] != '\0') {
        length++;
    }
    
    size_t out_max = length * 2 + 1;
    char* output = malloc(out_max);
    if (output == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[A-Z][a-z0-9]*", REG_EXTENDED);
    if (reti) {
        free(output);
        return NULL;
    }

    regmatch_t matches[1];
    const char* p = input;
    size_t out_index = 0;

    while (1) {
        reti = regexec(&regex, p, 1, matches, 0);
        if (reti == 0) {
            size_t match_len = (size_t)(matches[0].rm_eo - matches[0].rm_so);
            
            if (matches[0].rm_so > 0) {
                if (out_index + matches[0].rm_so < out_max) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(output + out_index, p, matches[0].rm_so);
                    out_index += matches[0].rm_so;
                }
            }
            
            if (out_index > 0 && output[out_index - 1] != ' ') {
                if (out_index < out_max - 1) {
                    output[out_index++] = ' ';
                }
            }
            
            if (out_index + match_len < out_max) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(output + out_index, p + matches[0].rm_so, match_len);
                out_index += match_len;
            }
            
            p += matches[0].rm_eo;
        } else if (reti == REG_NOMATCH) {
            if (out_index < out_max) {
                snprintf(output + out_index, out_max - out_index, "%s", p);
            }
            break;
        } else {
            regfree(&regex);
            free(output);
            return NULL;
        }
    }

    regfree(&regex);
    return output;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsACFunction";
    char* result = add_spaces_regex(test_str);
    
    if (result != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }
    
    return 0;
}