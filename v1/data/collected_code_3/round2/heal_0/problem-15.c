#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_string(char *str) {
    int i, j = 0, k = 0;
    char **result = malloc(sizeof(char *) * strlen(str));

    for(i = 0; i < strlen(str); i++) {
        if(islower(str[i])) {
            str[i] = '\0';
            result[j] = &str[k];
            j++;
            k = i + 1;
        }
    }
    result[j] = &str[k];
    return result;
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    char **result = split_string(str);
    int i = 0;

    while(result[i]) {
        printf("%s\n", result[i]);
        i++;
    }

    free(result);
    return 0;
}