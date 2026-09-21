#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, " +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *result = malloc(str_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t read_pos = 0;
    size_t write_pos = 0;

    while (read_pos < str_len) {
        if (regexec(&regex, str + read_pos, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + write_pos, str + read_pos, match.rm_so);
                write_pos += match.rm_so;
            }
            result[write_pos++] = ' ';
            read_pos += match.rm_eo;
        } else {
            size_t remaining = str_len - read_pos;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + write_pos, str + read_pos, remaining);
            write_pos += remaining;
            break;
        }
    }

    result[write_pos] = '\0';
    regfree(&regex);

    char *shrunk = realloc(result, write_pos + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *res = remove_multiple_spaces("Hello    world!  This   is a    test.");
    if (res != NULL) {
        printf("%s\n", res);
        free(res);
    }
    return 0;
}