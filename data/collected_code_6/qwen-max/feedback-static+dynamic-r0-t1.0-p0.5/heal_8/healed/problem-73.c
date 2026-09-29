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

    char **result = (char **)malloc((MAX_TOKENS + 1) * sizeof(char *));
    if (!result) {
        return -1;
    }

    for (size_t i = 0; i <= strlen(input); ) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            if (matches[0].rm_so > 0 && token_index < MAX_TOKENS) {
                result[token_index] = (char *)malloc((matches[0].rm_so + 1) * sizeof(char));
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
                size_t remaining_len = input[i] ? strlen(input + i) : 0;
                result[token_index] = (char *)malloc((remaining_len + 1) * sizeof(char));
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