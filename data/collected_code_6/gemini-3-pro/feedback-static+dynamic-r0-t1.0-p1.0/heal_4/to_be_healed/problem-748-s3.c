#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces_regex(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);
    
    size_t out_max = length * 2 + 1;
    char* output = malloc(out_max);
    if (output == NULL) {
        return NULL;
    }
    output[0] = '\0';

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
            size_t match_so = (size_t)matches[0].rm_so;
            size_t match_eo = (size_t)matches[0].rm_eo;
            size_t match_len = match_eo - match_so;
            
            if (match_so > 0) {
                for (size_t i = 0; i < match_so; i++) {
                    if (out_index < out_max - 1) {
                        output[out_index++] = p[i];
                    }
                }
            }
            
            if (out_index > 0 && output[out_index - 1] != ' ') {
                if (out_index < out_max - 1) {
                    output[out_index++] = ' ';
                }
            }
            
            for (size_t i = 0; i < match_len; i++) {
                if (out_index < out_max - 1) {
                    output[out_index++] = p[match_so + i];
                }
            }
            
            p += match_eo;
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

    output[out_max - 1] = '\0';
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