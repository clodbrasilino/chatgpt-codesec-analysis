#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

void remove_uppercase_substrings(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    
    if (regcomp(&regex, "[A-Z]+", REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         */
        size_t len = strlen(str);
        char *new_str = (char *)malloc(len + 1);
        if (new_str == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        
        while (reti == 0) {
            reti = regexec(&regex, str, 0, NULL, 0);
            if (reti == 0) {
                /* Possible weaknesses found:
                 *  The scope of the variable 'match_end' can be reduced. [variableScope]
                 *  The scope of the variable 'match_start' can be reduced. [variableScope]
                 */
                size_t match_start, match_end;
                regoff_t ovector[6];
                /* Possible weaknesses found:
                 *  passing argument 4 of 'regexec' from incompatible pointer type [-Wincompatible-pointer-types]
                 */
                reti = regexec(&regex, str, 3, ovector, 0);
                if (reti == 0) {
                    match_start = ovector[0];
                    match_end = ovector[1];
                    /* Possible weaknesses found:
                     *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
                     *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                     *  include the header <string.h> or explicitly provide a declaration for 'memmove'
                     *  include '<string.h>' or provide a declaration of 'memmove'
                     */
                    memmove(str + match_start, str + match_end, len - match_end + 1);
                    len -= (match_end - match_start);
                }
            }
        }
        
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'strcpy'
         *  call to undeclared library function 'strcpy' with type 'char *(char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include '<string.h>' or provide a declaration of 'strcpy'
         *  implicit declaration of function 'strcpy' [-Wimplicit-function-declaration]
         */
        strcpy(new_str, str);
        free(new_str);
    } else if (reti == REG_NOMATCH) {
        // No uppercase substrings found
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
    
    regfree(&regex);
}

int main() {
    char str[] = "aBcDeFgHiJkLmNoP";
    remove_uppercase_substrings(str);
    printf("%s\n", str);
    return 0;
}