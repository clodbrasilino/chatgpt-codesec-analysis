#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces_capitals(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t cap = len * 2 + 2;
    char *result = malloc(cap);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED);
    if (reti != 0) {
        free(result);
        return NULL;
    }

    size_t res_idx = 0;
    const char *p = str;

    while (*p) {
        regmatch_t match;
        reti = regexec(&regex, p, 1, &match, 0);
        if (reti == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining_len = strlen(p);
            if (remaining_len > 0 && res_idx + remaining_len < cap) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, p, remaining_len);
                res_idx += remaining_len;
            }
            break;
        } else if (reti != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        } else {
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_so>0' is not redundant
             */
            if (match.rm_so > 0) {
                /* Possible weaknesses found:
                 *  Assignment 'copy_len=(unsigned long)match.rm_so', assigned value is greater than 0
                 */
                size_t copy_len = (size_t)match.rm_so;
                /* Possible weaknesses found:
                 *  Condition 'copy_len>0' is always true
                 *  Condition 'copy_len>0' is always true [knownConditionTrueFalse]
                 */
                if (copy_len > 0 && res_idx + copy_len < cap) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + res_idx, p, copy_len);
                    res_idx += copy_len;
                }
            }
            if (p != str && res_idx > 0) {
                if (res_idx + 1 < cap) {
                    result[res_idx++] = ' ';
                }
            }
            size_t match_len = match.rm_eo - match.rm_so;
            if (match_len > 0 && res_idx + match_len < cap) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, p + match.rm_so, match_len);
                res_idx += match_len;
            }
            p += match.rm_eo;
        }
    }

    if (res_idx < cap) {
        result[res_idx] = '\0';
    } else {
        result[cap - 1] = '\0';
    }

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