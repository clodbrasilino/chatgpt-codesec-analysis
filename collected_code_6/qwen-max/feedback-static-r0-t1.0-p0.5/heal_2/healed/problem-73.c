#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_TOKENS 100

int split_string(const char *input, const char *delimiters, char ***tokens) {
    regex_t regex;
    regmatch_t matches[1];
    int token_index = 0;
    size_t input_len = strlen(input);
    char **result = (char **)malloc(MAX_TOKENS * sizeof(char *));
    if (!result) return -1;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE)) {
        free(result);
        return -1;
    }

    for (size_t i = 0; i <= input_len; ) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            if (matches[0].rm_so > 0 && token_index < MAX_TOKENS) {
                size_t len = i + matches[0].rm_so;
                result[token_index] = (char *)malloc(len + 1);
                if (!result[token_index]) {
                    for (int j = 0; j < token_index; ++j) free(result[j]);
                    free(result);
                    regfree(&regex);
                    return -1;
                }
                memcpy(result[token_index], input + i, len);
                result[token_index][len] = '\0';
                token_index++;
            }
            i += matches[0].rm_eo;
        } else {
            if (token_index < MAX_TOKENS) {
                size_t len = input_len - i;
                result[token_index] = (char *)malloc(len + 1);
                if (!result[token_index]) {
                    for (int j = 0; j < token_index; ++j) free(result[j]);
                    free(result);
                    regfree(&regex);
                    return -1;
                }
                memcpy(result[token_index], input + i, len);
                result[token_index][len] = '\0';
                token_index++;
            }
            break;
        }
    }

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