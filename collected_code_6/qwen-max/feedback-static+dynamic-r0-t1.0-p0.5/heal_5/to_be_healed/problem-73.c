#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_TOKENS 100

int split_string(const char *input, const char *delimiters, char ***tokens) {
    regex_t regex;
    regmatch_t matches[1];
    int token_index = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len == 0) return -1;

    char **result = (char **)malloc((MAX_TOKENS + 1) * sizeof(char *));
    if (!result) return -1;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE)) {
        free(result);
        return -1;
    }

    for (size_t i = 0; i <= input_len; ) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            if (matches[0].rm_so > 0 && token_index < MAX_TOKENS) {
                /* Possible weaknesses found:
                 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                 */
                result[token_index] = (char *)malloc(((matches[0].rm_so + 1) * sizeof(char)));
                if (!result[token_index]) {
                    for (int j = 0; j < token_index; ++j) free(result[j]);
                    free(result);
                    regfree(&regex);
                    return -1;
                }
                memmove(result[token_index], input + i, matches[0].rm_so);
                result[token_index][matches[0].rm_so] = '\0';
                token_index++;
            }
            i += matches[0].rm_eo;
        } else {
            if (token_index < MAX_TOKENS) {
                size_t remaining_len = input_len - i;
                result[token_index] = (char *)malloc(((remaining_len + 1) * sizeof(char)));
                if (!result[token_index]) {
                    for (int j = 0; j < token_index; ++j) free(result[j]);
                    free(result);
                    regfree(&regex);
                    return -1;
                }
                memmove(result[token_index], input + i, remaining_len);
                result[token_index][remaining_len] = '\0';
                token_index++;
            }
            break;
        }
    }

    result[token_index] = NULL;
    *tokens = result;
    regfree(&regex);
    return token_index;
}

int main() {
    const char *input = "This is a test string, with multiple: delimiters.";
    const char *delimiters = "[ ,:.]+";
    char **tokens;
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