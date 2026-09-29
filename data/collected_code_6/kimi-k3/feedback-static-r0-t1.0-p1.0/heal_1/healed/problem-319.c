#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_five_char_words(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *cursor = str;
    int ret;

    ret = regcomp(&regex, "\\b[a-zA-Z]{5}\\b", REG_EXTENDED);
    if (ret != 0) {
        size_t error_buf_size = regerror(ret, &regex, NULL, 0);
        char *error_buf = malloc(error_buf_size);
        if (error_buf == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        regerror(ret, &regex, error_buf, error_buf_size);
        fprintf(stderr, "Regex compilation failed: %s\n", error_buf);
        free(error_buf);
        return;
    }

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            size_t error_buf_size = regerror(ret, &regex, NULL, 0);
            char *error_buf = malloc(error_buf_size);
            if (error_buf == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                break;
            }
            regerror(ret, &regex, error_buf, error_buf_size);
            fprintf(stderr, "Regex execution failed: %s\n", error_buf);
            free(error_buf);
            break;
        }

        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), cursor + match.rm_so);
        cursor += match.rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "Here are some words apple tree house seven eight nine ten eleven";
    find_five_char_words(text);
    return 0;
}