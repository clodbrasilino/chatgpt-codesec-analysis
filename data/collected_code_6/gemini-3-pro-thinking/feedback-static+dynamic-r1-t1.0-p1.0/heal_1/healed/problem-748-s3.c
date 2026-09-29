#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *insert_spaces(const char *input) {
    regex_t regex;
    int ret;
    size_t len = 0;
    size_t max_input = 8192;
    char *result;
    const char *cursor;
    char *out;
    size_t rem_out;
    regmatch_t pmatch[1];

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    while (input[len] != '\0' && len < max_input) {
        len++;
    }

    if (len == max_input || len > ((size_t)-1 / 2) - 1) {
        regfree(&regex);
        return NULL;
    }

    size_t max_out_len = len * 2 + 1;
    result = (char *)malloc(max_out_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    out = result;
    rem_out = max_out_len;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t offset = (size_t)pmatch[0].rm_so;

        if (offset > 0) {
            if (offset >= rem_out) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(out, cursor, offset);
            out += offset;
            rem_out -= offset;
        }

        if ((cursor + offset) > input) {
            if (*(cursor + offset - 1) != ' ') {
                if (rem_out < 2) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                *out = ' ';
                out++;
                rem_out--;
            }
        }

        if (rem_out < 2) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        
        *out = cursor[offset];
        out++;
        rem_out--;
        cursor += offset + 1;

        if (*cursor == '\0') {
            break;
        }
    }

    if (rem_out > 0) {
        snprintf(out, rem_out, "%s", cursor);
    }

    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_str = "HelloWorldThisIsATest";
    char *spaced_str;

    spaced_str = insert_spaces(test_str);
    if (spaced_str != NULL) {
        printf("%s\n", spaced_str);
        free(spaced_str);
    }

    return 0;
}