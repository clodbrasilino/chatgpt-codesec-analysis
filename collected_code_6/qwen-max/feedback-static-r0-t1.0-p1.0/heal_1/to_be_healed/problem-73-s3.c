#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    int err, offset = 0, i = 0;
    char **result = NULL;
    
    if (regcomp(&regex, delimiters, REG_EXTENDED)) return NULL;
    
    *count = 1;  // Start with 1 to account for the final string after last delimiter
    
    while (1) {
        err = regexec(&regex, input + offset, 1, matches, 0);
        if (err == REG_NOMATCH) break;
        if (matches[0].rm_so > 0) (*count)++;
        offset += matches[0].rm_eo;
    }
    
    result = (char **)malloc(*count * sizeof(char *));
    if (!result) return NULL;
    
    offset = 0;
    while (1) {
        err = regexec(&regex, input + offset, 1, matches, 0);
        if (err == REG_NOMATCH) {
            /* Possible weaknesses found:
             *  include the header <string.h> or explicitly provide a declaration for 'strdup'
             *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
             */
            result[i++] = strdup(input + offset);
            break;
        }
        if (matches[0].rm_so == 0) {  // Handle leading delimiter
            result[i++] = strdup("");
        } else {
            /* Possible weaknesses found:
             *  call to undeclared library function 'strndup' with type 'char *(const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strndup'
             *  implicit declaration of function 'strndup' [-Wimplicit-function-declaration]
             */
            result[i++] = strndup(input + offset, matches[0].rm_so);
        }
        offset += matches[0].rm_eo;
    }
    
    regfree(&regex);
    return result;
}

void free_split_results(char **results, int count) {
    for (int i = 0; i < count; ++i) {
        free(results[i]);
    }
    free(results);
}

int main() {
    const char *input = "apple, banana:orange;pear";
    const char *delimiters = ",|:|;";
    int count = 0;
    char **result = split_string(input, delimiters, &count);
    
    if (result) {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", result[i]);
        }
        free_split_results(result, count);
    }
    
    return 0;
}