#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  to match this '{'
 */
int remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match;
    size_t read = 0;
    size_t write = 0;
    size_t len;
    int ret;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Unmatched '{'. Configuration: ''. [syntaxError]
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     *  to match this '{'
     */
    while (str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ret = regexec(&regex, str + read, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            len = strlen(str + read);
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            memmove(str + write, str + read, len + 1);
            write += len;
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            return -1;
        }

        len = (size_t)match.rm_so;
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            memmove(str + write, str + read, len);
            write += len;
        }

        if (match.rm_eo == match.rm_so) {
            str[write++] = str[read++];
            continue;
        }

        /* Possible weaknesses found:
         *  expected '}'
         *  expected expression at end of input
         *  expected declaration or statement at end of input
         *  expected expression
         */
        read += (