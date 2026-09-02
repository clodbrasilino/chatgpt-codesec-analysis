#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     */
    char *str = strdup(input);
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    int len = strlen(str);
    int offset = 0;
    int nmatch = 1;
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     */
    int i, j;
    char **result = NULL;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE) != 0) {
        free(str);
        return NULL;
    }

    *count = 0;
    while (regexec(&regex, str + offset, nmatch, matches, 0) == 0) {
        if (matches[0].rm_so > 0) {
            (*count)++;
        }
        offset += matches[0].rm_eo;
    }
    if (offset < len) {
        (*count)++;
    }

    result = (char **)malloc((*count + 1) * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        free(str);
        return NULL;
    }

    *count = 0;
    offset = 0;
    while (regexec(&regex, str + offset, nmatch, matches, 0) == 0) {
        if (matches[0].rm_so > 0) {
            result[*count] = (char *)malloc(matches[0].rm_so * sizeof(char));
            if (result[*count] == NULL) {
                for (i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                free(str);
                return NULL;
            }
            /* Possible weaknesses found:
             *  include '<string.h>' or provide a declaration of 'strncpy'
             *  include the header <string.h> or explicitly provide a declaration for 'strncpy'
             *  call to undeclared library function 'strncpy' with type 'char *(char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
             */
            strncpy(result[*count], str + offset, matches[0].rm_so);
            result[*count][matches[0].rm_so] = '\0';
            (*count)++;
        }
        offset += matches[0].rm_eo;
    }
    if (offset < len) {
        result[*count] = (char *)malloc((len - offset + 1) * sizeof(char));
        if (result[*count] == NULL) {
            for (i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            free(str);
            return NULL;
        }
        strncpy(result[*count], str + offset, len - offset);
        result[*count][len - offset] = '\0';
        (*count)++;
    }
    result[*count] = NULL;

    regfree(&regex);
    free(str);
    return result;
}

int main() {
    const char *input = "apple,orange;banana|grape";
    const char *delimiters = ",;|";
    int count;
    char **result = split_string(input, delimiters, &count);

    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        fprintf(stderr, "Failed to split string\n");
    }

    return 0;
}