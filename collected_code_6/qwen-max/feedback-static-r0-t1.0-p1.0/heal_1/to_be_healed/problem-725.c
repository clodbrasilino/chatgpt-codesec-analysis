#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memcpy'
  */

char **extract_quoted_values(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "\"([^\"]*)\"";
    char *str = (char *)input;
    char **result = NULL;
    *count = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        return NULL;
    }

    while (regexec(&regex, str, 2, matches, 0) == 0) {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
         */
        result = realloc(result, (*count + 1) * sizeof(char *));
        if (result == NULL) {
            regfree(&regex);
            return NULL;
        }
        result[*count] = malloc(matches[1].rm_eo - matches[1].rm_so + 1);
        if (result[*count] == NULL) {
            for (int i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'memcpy'
         *  implicit declaration of function 'memcpy' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'memcpy' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        memcpy(result[*count], &str[matches[1].rm_so], matches[1].rm_eo - matches[1].rm_so);
        result[*count][matches[1].rm_eo - matches[1].rm_so] = '\0';
        *count += 1;
        str += matches[0].rm_eo;
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *input = "This is a \"test\" string with multiple \"quoted values\".";
    int count;
    char **values = extract_quoted_values(input, &count);

    if (values != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }

    return 0;
}