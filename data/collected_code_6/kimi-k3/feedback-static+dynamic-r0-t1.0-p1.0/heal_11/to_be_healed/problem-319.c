#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_five_char_words(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *cursor = str;
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_buf[256];

    if (str == NULL) {
        fprintf(stderr, "Invalid input: NULL string\n");
        return;
    }

    ret = regcomp(&regex, "\\b[a-zA-Z]{5}\\b", REG_EXTENDED);
    if (ret != 0) {
        size_t err_len = regerror(ret, &regex, NULL, 0);
        if (err_len > 0 && err_len <= sizeof(error_buf)) {
            regerror(ret, &regex, error_buf, sizeof(error_buf));
        } else {
            snprintf(error_buf, sizeof(error_buf), "Unknown regex error");
        }
        fprintf(stderr, "Regex compilation failed: %s\n", error_buf);
        return;
    }

    size_t str_len = strnlen(str, 1024 * 1024);

    while (*cursor != '\0' && (size_t)(cursor - str) < str_len) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            size_t err_len = regerror(ret, &regex, NULL, 0);
            if (err_len > 0 && err_len <= sizeof(error_buf)) {
                regerror(ret, &regex, error_buf, sizeof(error_buf));
            } else {
                snprintf(error_buf, sizeof(error_buf), "Unknown regex error");
            }
            fprintf(stderr, "Regex execution failed: %s\n", error_buf);
            break;
        }

        if (match.rm_so >= 0 && match.rm_eo > match.rm_so) {
            size_t match_len = (size_t)(match.rm_eo - match.rm_so);
            size_t remaining = str_len - (size_t)(cursor - str);
            if (match_len <= remaining) {
                printf("%.*s\n", (int)match_len, cursor + match.rm_so);
                cursor += match.rm_eo;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "Here are some words apple tree house seven eight nine ten eleven";
    find_five_char_words(text);
    return 0;
}