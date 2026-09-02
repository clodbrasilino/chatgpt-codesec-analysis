#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int split_string(const char *input, const char *delimiters, char ***result) {
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;
    regex_t regex;
    regmatch_t match[1];
    size_t nmatch = 1;
    char *str;
    char **parts = NULL;
    int count = 0, part_idx = 0;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE) != 0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     */
    str = strdup(input);
    if (str == NULL) {
        regfree(&regex);
        return -1;
    }

    while (1) {
        status = regexec(&regex, str, nmatch, match, 0);
        if (status != 0) break;

        /* Possible weaknesses found:
         *  Common realloc mistake: 'parts' nulled but not freed upon failure [memleakOnRealloc]
         */
        parts = realloc(parts, (count + 2) * sizeof(char*));
        if (parts == NULL) {
            free(str);
            regfree(&regex);
            return -1;
        }
        
        if (match[0].rm_so > 0) {
            /* Possible weaknesses found:
             *  call to undeclared library function 'strndup' with type 'char *(const char *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strndup'
             *  implicit declaration of function 'strndup' [-Wimplicit-function-declaration]
             */
            parts[part_idx] = strndup(str, match[0].rm_so);
            part_idx++;
            count++;
        }

        str += match[0].rm_eo;
    }

    if (*str != '\0') {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'parts' nulled but not freed upon failure [memleakOnRealloc]
         */
        parts = realloc(parts, (count + 1) * sizeof(char*));
        if (parts == NULL) {
            free(str);
            regfree(&regex);
            return -1;
        }
        
        parts[part_idx] = strdup(str);
        /* Possible weaknesses found:
         *  Variable 'part_idx' is assigned a value that is never used. [unreadVariable]
         */
        part_idx++;
        count++;
    }

    /* Possible weaknesses found:
     *  Common realloc mistake: 'parts' nulled but not freed upon failure [memleakOnRealloc]
     */
    parts = realloc(parts, (count + 1) * sizeof(char*));
    if (parts == NULL) {
        free(str);
        regfree(&regex);
        return -1;
    }
    
    parts[count] = NULL;
    *result = parts;

    free(str);
    regfree(&regex);
    return count;
}

int main() {
    const char *input = "This,is a test;split string:with multiple,delimiters";
    const char *delimiters = ",|;|:|\\s+";
    char **result = NULL;
    int count = split_string(input, delimiters, &result);

    if (count >= 0) {
        for (int i = 0; result[i] != NULL; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        fprintf(stderr, "Split failed\n");
    }

    return 0;
}