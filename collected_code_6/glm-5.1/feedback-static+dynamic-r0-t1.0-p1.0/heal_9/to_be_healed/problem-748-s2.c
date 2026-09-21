#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces_capitals(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED);
    if (reti != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t buf_size = len * 2 + 2;
    char *result = malloc(buf_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    size_t remaining = buf_size - 1;
    const char *p = str;

    while (*p) {
        regmatch_t match;
        reti = regexec(&regex, p, 1, &match, 0);
        if (reti == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t source_len = strlen(p);
            if (source_len > 0) {
                size_t copy_len = source_len < remaining ? source_len : remaining;
                if (copy_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + res_idx, p, copy_len);
                    res_idx += copy_len;
                    /* Possible weaknesses found:
                     *  Variable 'remaining' is assigned a value that is never used. [unreadVariable]
                     *  Value stored to 'remaining' is never read [deadcode.DeadStores]
                     */
                    remaining -= copy_len;
                }
            }
            break;
        } else if (reti != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        } else {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so < remaining ? (size_t)match.rm_so : remaining;
                if (copy_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + res_idx, p, copy_len);
                    res_idx += copy_len;
                    remaining -= copy_len;
                }
            }
            if (p != str && res_idx > 0) {
                if (remaining > 0) {
                    result[res_idx++] = ' ';
                    remaining--;
                }
            }
            size_t match_len = match.rm_eo - match.rm_so;
            size_t actual_match_len = match_len < remaining ? match_len : remaining;
            if (actual_match_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, p + match.rm_so, actual_match_len);
                res_idx += actual_match_len;
                remaining -= actual_match_len;
            }
            p += match.rm_eo;
        }
    }

    result[res_idx] = '\0';

    regfree(&regex);
    return result;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *res = add_spaces_capitals(argv[1]);
    if (res == NULL) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    printf("%s\n", res);
    free(res);

    return 0;
}