#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1000

char **split_at_uppercase(char *str, int *len) {
    char **res = malloc(sizeof(char*) * MAX_LEN);
    for(int i = 0; i < MAX_LEN; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'res' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        res[i] = malloc(sizeof(char) * MAX_LEN);
    }

    int start = 0;
    int end = 0;
    int count = 0;
    while(str[end] != '\0') {
        if(isupper(str[end])) {
            strncpy(res[count], &str[start], end - start);
            res[count][end - start] = '\0';
            count++;
            start = end;
        }
        end++;
    } 
    strncpy(res[count], &str[start], end - start);
    res[count][end - start] = '\0';
    *len = count + 1;

    return res;
}

int main() {
    char input[MAX_LEN];
    int len = 0;
    
    printf("Enter the string: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = '\0';

    char **res = split_at_uppercase(input, &len);

    for(int i = 0; i < len; i++) {
        printf("%s\n", res[i]);
    }

    for(int i = 0; i < len; i++) {
        free(res[i]);
    }
    free(res);

    return 0;
}