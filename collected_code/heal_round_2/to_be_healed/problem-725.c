#include <stdio.h>
#include <regex.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void extractValues(const char* string) {
    regex_t regex;
    regmatch_t matches[1];
    const char* pattern = "\"([^\"]+)\""; 

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Could not compile regex pattern\n");
        return;
    }

    int result = regexec(&regex, string, 1, matches, 0);
    if (result == 0) {
        int start = matches[0].rm_so + 1;
        int end = matches[0].rm_eo - 1;
        /* Possible weaknesses found:
         *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'malloc'
         */
        char* extractedValue = malloc(sizeof(char) * (end - start + 1));

        if (extractedValue) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(extractedValue, string + start, end - start);
            extractedValue[end - start] = '\0';
            printf("%s\n", extractedValue);
            /* Possible weaknesses found:
             *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             *  include '<stdlib.h>' or provide a declaration of 'free'
             */
            free(extractedValue);
        } else {
            printf("Memory allocation failed.\n");
        }
    } else if (result == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        printf("Error executing regex\n");
    }

    regfree(&regex);
}

int main() {
    char string[] = "The value is \"example\".";
    extractValues(string);
    return 0;
}