#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  'ptrdiff_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
  */

#define MAX_MATCHES 2

char **extract_quoted_values(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    char **results = NULL;
    *count = 0;

    if (regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED) != 0) {
        return NULL;
    }

    const char *p = str;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'ptrdiff_t'
     *  unknown type name 'ptrdiff_t'
     */
    ptrdiff_t capacity = 10;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'capacity'
     */
    results = malloc(capacity * sizeof(char *));
    if (!results) {
        regfree(&regex);
        return NULL;
    }

    while (regexec(&regex, p, MAX_MATCHES, matches, 0) == 0) {
        if (matches[1].rm_so == -1) {
            break;
        }

        /* Possible weaknesses found:
         *  use of undeclared identifier 'capacity'
         */
        if (*count >= (size_t)capacity) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'capacity'
             */
            capacity *= 2;
            /* Possible weaknesses found:
             *  use of undeclared identifier 'capacity'
             */
            char **temp = realloc(results, capacity * sizeof(char *));
            if (!temp) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                return NULL;
            }
            results = temp;
        }

        /* Possible weaknesses found:
         *  'ptrdiff_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
         *  use of undeclared identifier 'ptrdiff_t'
         *  unknown type name 'ptrdiff_t'
         */
        ptrdiff_t len = matches[1].rm_eo - matches[1].rm_so;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'len'
         */
        if (len < 0) {
            break;
        }

        /* Possible weaknesses found:
         *  use of undeclared identifier 'len'
         */
        size_t ulen = (size_t)len;
        results[*count] = malloc(ulen + 1);
        if (!results[*count]) {
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            return NULL;
        }

        if (ulen > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(results[*count], p + matches[1].rm_so, ulen);
        }
        results[*count][ulen] = '\0';

        (*count)++;
        p += matches[0].rm_eo;
    }

    regfree(&regex);

    if (*count == 0) {
        free(results);
        return NULL;
    }

    char **shrunk = realloc(results, *count * sizeof(char *));
    if (shrunk) {
        return shrunk;
    }
    return results;
}

int main(void) {
    const char *text = "Hello \"World\", this is a \"test\" string with \"empty\" \"\" quotes.";
    size_t count = 0;
    char **values = extract_quoted_values(text, &count);

    if (values) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }

    return 0;
}