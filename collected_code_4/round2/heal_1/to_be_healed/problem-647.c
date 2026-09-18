#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SUBSTR 100
#define MAX_STR_LEN 1000

char **splitString(char *str, int *count){
    char **res = (char**)malloc(sizeof(char*)*MAX_SUBSTR);
    for(int i = 0; i < MAX_SUBSTR; i++){
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'res' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        res[i] = (char*)malloc(sizeof(char)*MAX_STR_LEN);
    }

    int j = 0, k = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(isupper(str[i])){
            res[j][k] = '\0';
            j++;
            k = 0;
        } else {
            res[j][k++] = str[i];
        }
    }
    res[j][k] = '\0';
    *count = j + 1;
    
    return res;
}

int main() {
    char str[] = "HelloWorldHowAreYou";
    int count;
    char **split = splitString(str, &count);

    for(int i = 0; i < count; i++){
        puts(split[i]);
    }

    for(int i = 0; i < count; i++){
        free(split[i]);
    }
    free(split);

    return 0;
}