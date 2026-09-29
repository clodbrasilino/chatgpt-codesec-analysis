#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

#define MAX 1000

void put_spaces(char* str) {
    regex_t regex;
    int ret;
    regmatch_t pmatch[2];
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     */
    char *tmp = malloc(strlen(str)+1);
    /* Possible weaknesses found:
     *  use of possibly-NULL 'tmp' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
     *  implicit declaration of function 'strcpy' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'strcpy' [-Wbuiltin-declaration-mismatch]
     *  include '<string.h>' or provide a declaration of 'strcpy'
     */
    strcpy(tmp, str);

    if (regcomp(&regex, "([A-Z])", REG_EXTENDED) != 0) {
        printf("Failed to compile regex\n");
        free(tmp);
        return;
    }
    while (regexec(&regex, tmp, 2, pmatch, 0) == 0) {
        tmp[pmatch[1].rm_eo] = '\0';
        printf("%s %s", tmp, tmp+pmatch[1].rm_so);
        /* Possible weaknesses found:
         *  leak of 'tmp' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        tmp += pmatch[1].rm_eo+1;
    }
    printf("%s\n", tmp);
    regfree(&regex);
    free(tmp);
}

int main()
{
    char str[MAX];
    printf("Enter a string: ");
    fgets(str, MAX, stdin);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  include '<string.h>' or provide a declaration of 'strlen'
     */
    str[strlen(str)-1] = '\0'; 
    put_spaces(str);
    return 0;
}