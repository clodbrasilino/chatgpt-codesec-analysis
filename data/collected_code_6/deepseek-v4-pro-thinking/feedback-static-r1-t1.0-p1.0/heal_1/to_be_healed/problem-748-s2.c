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

    if (str == NULL) {
        return NULL;
    }

    status = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    output = malloc(strlen(str) * 2 + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    src = str;
    dst = output;
    offset = 0;

    while ((status = regexec(&regex, src + offset, 1, &match, 0)) == 0) {
        size_t match_start = offset + match.rm_so;
        size_t match_end = offset + match.rm_eo;
        size_t seg_len = match_start - offset;

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst, src + offset, seg_len);
        dst += seg_len;

        if (match_start > 0 && !isspace((unsigned char)src[match_start - 1])) {
            *dst++ = ' ';
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst, src + match_start, match_end - match_start);
        dst += match_end - match_start;
        offset = match_end;
    }

    if (status != REG_NOMATCH) {
        regfree(&regex);
        free(output);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(dst, src + offset);
    regfree(&regex);
    return output;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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