#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t re;
    regmatch_t matches[10];
    char *str, *p;
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     *  The scope of the variable 'len' can be reduced. [variableScope]
     *  Variable 'match_count' is assigned a value that is never used. [unreadVariable]
     */
    int match_count = 0, i, j, len, m;
    char **result;

    if (regcomp(&re, delimiters, REG_EXTENDED|REG_NEWLINE)) return NULL;

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     */
    str = strdup(input);
    if (str == NULL) return NULL;

    *count = 1;
    m = regexec(&re, str, 9, matches, 0);
    while (m == 0) {
        (*count)++;
        m = regexec(&re, str + matches[0].rm_eo, 9, matches, 0);
    }

    result = malloc(*count * sizeof(char *));
    /* Possible weaknesses found:
     *  implicit declaration of function 'strtok'; did you mean 'strtoq'? [-Wimplicit-function-declaration]
     *  assignment to 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  include the header <string.h> or explicitly provide a declaration for 'strtok'
     *  call to undeclared library function 'strtok' with type 'char *(char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    p = strtok(str, delimiters);
    for (i = 0; p != NULL && i < *count; i++) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         */
        len = strlen(p);
        result[i] = malloc((len + 1) * sizeof(char));
        /* Possible weaknesses found:
         *  call to undeclared library function 'strncpy' with type 'char *(char *, const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include '<string.h>' or provide a declaration of 'strncpy'
         *  include the header <string.h> or explicitly provide a declaration for 'strncpy'
         *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
         */
        strncpy(result[i], p, len);
        result[i][len] = '\0';
        /* Possible weaknesses found:
         *  assignment to 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         */
        p = strtok(NULL, delimiters);
    }

    free(str);
    regfree(&re);
    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'input' can be declared as pointer to const [constVariablePointer]
     */
    char *input = "apple,banana;orange:lemon";
    /* Possible weaknesses found:
     *  Variable 'delimiters' can be declared as pointer to const [constVariablePointer]
     */
    char *delimiters = ",;:";
    int count;

    char **result = split_string(input, delimiters, &count);

    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}