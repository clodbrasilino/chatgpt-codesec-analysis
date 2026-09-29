#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *insert_spaces(const char *str) {
    regex_t regex;
    regmatch_t match;
    char *output;
    size_t max_len, pos, offset;
    int status;

    if (str == NULL) {
        return NULL;
    }

    status = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    max_len = strlen(str) * 2 + 1;
    output = malloc(max_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    pos = 0;
    offset = 0;

    while ((status = regexec(&regex, str + offset, 1, &match, 0)) == 0) {
        size_t match_start = offset + match.rm_so;
        size_t match_end = offset + match.rm_eo;
        size_t seg_len = match_start - offset;

        if (pos + seg_len >= max_len) {
            regfree(&regex);
            free(output);
            return NULL;
        }
        memcpy(output + pos, str + offset, seg_len);
        pos += seg_len;

        if (match_start > 0 && !isspace((unsigned char)str[match_start - 1])) {
            if (pos >= max_len - 1) {
                regfree(&regex);
                free(output);
                return NULL;
            }
            output[pos++] = ' ';
        }

        {
            size_t match_len = match_end - match_start;
            if (pos + match_len >= max_len) {
                regfree(&regex);
                free(output);
                return NULL;
            }
            memcpy(output + pos, str + match_start, match_len);
            pos += match_len;
        }
        offset = match_end;
    }

    if (status != REG_NOMATCH) {
        regfree(&regex);
        free(output);
        return NULL;
    }

    {
        size_t remaining_len = strlen(str + offset);
        if (pos + remaining_len >= max_len) {
            regfree(&regex);
            free(output);
            return NULL;
        }
        memcpy(output + pos, str + offset, remaining_len);
        pos += remaining_len;
    }

    output[pos] = '\0';
    regfree(&regex);
    return output;
}

int main(void) {
    char input[1024];
    char *result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';

    result = insert_spaces(input);
    if (result == NULL) {
        fputs("Error processing string\n", stderr);
        return 1;
    }

    puts(result);
    free(result);
    return 0;
}