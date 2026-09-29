#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_TOKENS 100

int split_string(const char *input, const char *delimiters, char ***tokens) {
    regex_t regex;
    regmatch_t matches[1];
    int token_index = 0;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE)) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    for (size_t i = 0; i <= input_len; ) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            if (matches[0].rm_so > 0 && token_index < MAX_TOKENS) {
                size_t len = matches[0].rm_so;
                (*tokens)[token_index] = malloc(len + 1);
                if (!(*tokens)[token_index]) {
                    for (int j = 0; j < token_index; ++j) free((*tokens)[j]);
                    free(*tokens);
                    regfree(&regex);
                    return -1;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy((*tokens)[token_index], input + i, len);
                (*tokens)[token_index][len] = '\0';
                token_index++;
            }
            i += matches[0].rm_eo;
        } else {
            if (token_index < MAX_TOKENS) {
                size_t remaining_len = input_len - i;
                (*tokens)[token_index] = malloc(remaining_len + 1);
                if (!(*tokens)[token_index]) {
                    for (int j = 0; j < token_index; ++j) free((*tokens)[j]);
                    free(*tokens);
                    regfree(&regex);
                    return -1;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy((*tokens)[token_index], input + i, remaining_len);
                (*tokens)[token_index][remaining_len] = '\0';
                token_index++;
            }
            break;
        }
    }

    regfree(&regex);
    return token_index;
}

int main() {
    const char *input = "This is a test string, with multiple: delimiters.";
    const char *delimiters = "[ ,:.]+";
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens) return -1;

    int count = split_string(input, delimiters, &tokens);

    if (count >= 0) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", tokens[i]);
            free(tokens[i]);
        }
        free(tokens);
    } else {
        fprintf(stderr, "Error splitting string.\n");
    }

    return 0;
}