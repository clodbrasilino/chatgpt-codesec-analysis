#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_with_colon(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_offset = 0;
    size_t dest_offset = 0;
    regmatch_t match;

    while (regexec(&regex, str + src_offset, 1, &match, 0) == 0) {
        if (match.rm_so == -1) {
            break;
        }

        size_t match_start = src_offset + match.rm_so;
        size_t match_end = src_offset + match.rm_eo;

        size_t non_match_len = match_start - src_offset;
        if (dest_offset + non_match_len > len) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dest_offset, str + src_offset, non_match_len);
        dest_offset += non_match_len;

        if (dest_offset + 1 > len) {
            break;
        }
        result[dest_offset] = ':';
        dest_offset++;

        src_offset = match_end;
    }

    if (dest_offset < len + 1) {
        snprintf(result + dest_offset, len + 1 - dest_offset, "%s", str + src_offset);
    } else {
        result[len] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *input = "hello world, this.is a test";
    char *output = replace_with_colon(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}