#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void removeLowercaseSubstrings(char *str){   
    regex_t regex;
    char *result = malloc(sizeof(char) * strlen(str)+1);
    int index = 0;

    if(regcomp(&regex, "[a-z]+", REG_EXTENDED) == 0){
        regmatch_t match;

        while(regexec(&regex, str, 1, &match, 0) == 0){
            for(int i = 0; i<match.rm_so; i++, index++){
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                result[index] = str[i];
            }

            str += match.rm_eo;
        }

        for(int i = 0; i<strlen(str)+1; i++, index++){
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[index] = str[i];
        }

        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        result[index] = '\0';
    }

    strcpy(str, result);
    free(result);
    regfree(&regex);
}

int main(){
    char str[] = "Hello, I'm a LowerCase STRING";
    removeLowercaseSubstrings(str);
    printf("%s\n", str);
    return 0;
}
