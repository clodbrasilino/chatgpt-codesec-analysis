#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define MAX 1000

void put_spaces(char* str) {
    regex_t regex;
    int ret;
    regmatch_t pmatch[2];
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *tmp = malloc(strlen(str)+1);
    /* Possible weaknesses found:
     *  call to undeclared library function 'strcpy' with type 'char *(char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strcpy'
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
    str[strlen(str)-1] = '\0'; 
    put_spaces(str);
    return 0;
}