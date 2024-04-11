#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* camel_to_snake(char* input) {
    int length = strlen(input);
    char* result = (char*)malloc(sizeof(char) * (2 * length));
    if (result == NULL) {
        return NULL;
    }
    int index = 0;

    for(int i = 0; i < length; i++) {
        if(isupper(input[i])) {
            result[index] = '_';
            index++;
            result[index] = tolower(input[i]);
        } else {
            result[index] = input[i];
        }
        index++;
    }
    result[index] = '\0';
    return result;
}

int main() {
    char input[] = "camelCaseString";
    char* result = camel_to_snake(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error in memory allocation\n");
        return 1;
    }
    return 0;
}