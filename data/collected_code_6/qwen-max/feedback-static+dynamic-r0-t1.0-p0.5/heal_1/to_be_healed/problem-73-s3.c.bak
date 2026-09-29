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
     *  The scope of the variable 'p' can be reduced. [variableScope]
     *  Unused variable: saveptr [unusedVariable]
     */
    char *str, *p, *saveptr;
    int nmatch = 1, offset = 0, i = 0;
    char **result = NULL;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    str = strdup(input);
    if (!str) {
        regfree(&regex);
        return NULL;
    }

    result = malloc(sizeof(char *));
    if (!result) {
        free(str);
        regfree(&regex);
        return NULL;
    }
    *result = NULL;
    *count = 0;

    while (regexec(&regex, str + offset, nmatch, matches, 0) == 0) {
        /* Possible weaknesses found:
         *  Variable 'p' is assigned a value that is never used. [unreadVariable]
         */
        p = str + offset + matches[0].rm_eo;
        if (matches[0].rm_so > 0) {
            /* Possible weaknesses found:
             *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
             */
            result = realloc(result, (i + 2) * sizeof(char *));
            if (!result) {
                free(str);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             *  call to undeclared library function 'strndup' with type 'char *(const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strndup' [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strndup'
             */
            result[i] = strndup(str + offset, matches[0].rm_so - offset);
            if (!result[i]) {
                for (int j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                free(str);
                regfree(&regex);
                return NULL;
            }
            i++;
            *count = i;
        }
        offset += matches[0].rm_eo;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    if (offset < (int)strlen(str)) {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
         */
        result = realloc(result, (i + 2) * sizeof(char *));
        if (!result) {
            free(str);
            regfree(&regex);
            return NULL;
        }
        result[i] = strdup(str + offset);
        if (!result[i]) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(str);
            regfree(&regex);
            return NULL;
        }
        i++;
        *count = i;
    }

    /* Possible weaknesses found:
     *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
     */
    result = realloc(result, (i + 1) * sizeof(char *));
    /* Possible weaknesses found:
     *  Assuming that condition '!result' is not redundant
     */
    if (!result) {
        for (int j = 0; j < i; j++) {
            /* Possible weaknesses found:
             *  Either the condition '!result' is redundant or there is possible null pointer dereference: result. [nullPointerRedundantCheck]
             *  Null pointer dereference
             */
            free(result[j]);
        }
        free(result);
        free(str);
        regfree(&regex);
        return NULL;
    }
    result[i] = NULL;

    free(str);
    regfree(&regex);
    return result;
}

int main() {
    const char *input = "apple,orange;banana|grape";
    const char *delimiters = ",;|";
    int count = 0;
    char **result = split_string(input, delimiters, &count);

    if (result) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}