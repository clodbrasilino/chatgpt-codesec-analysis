#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *insert_spaces(const char *str) {
    regex_t regex;
    regmatch_t match;
    char *output;
    const char *src;
    char *dst;
    size_t offset;
    int status;
    size_t total_len;
    size_t remaining;

    if (str == NULL) {
        return NULL;
    }

    status = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    total_len = strlen(str) * 2 + 1;
    output = malloc(total_len);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    src = str;
    dst = output;
    offset = 0;
    remaining = total_len;

    while ((status = regexec(&regex, src + offset, 1, &match, 0)) == 0) {
        size_t match_start = offset + match.rm_so;
        size_t match_end = offset + match.rm_eo;
        size_t seg_len = match_start - offset;
        size_t match_len = match_end - match_start;

        if (seg_len >= remaining) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        memcpy(dst, src + offset, seg_len);
        dst += seg_len;
        remaining -= seg_len;

        if (match_start > 0 && !isspace((unsigned char)src[match_start - 1])) {
            if (remaining < 1) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            *dst++ = ' ';
            remaining--;
        }

        if (match_len >= remaining) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        memcpy(dst, src + match_start, match_len);
        dst += match_len;
        remaining -= match_len;
        offset = match_end;
    }

    if (status != REG_NOMATCH) {
        free(output);
        regfree(&regex);
        return NULL;
    }

    {
        size_t tail_len = strlen(src + offset);
        if (tail_len + 1 > remaining) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        memcpy(dst, src + offset, tail_len);
        dst[tail_len] = '\0';
    }

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