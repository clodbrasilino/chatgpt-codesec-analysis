#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

char* snakeToCamel(const char *input) {
    int length = strlen(input);
    char *output = (char *) malloc((length + 1) * sizeof(char));
    
    if (!output) {
        return NULL;
    }

    int i = 0;
    int j = 0;

    while(i < length) {
        if(input[i] == '_') {
            i++;
            if(i < length) {
                output[j] = toupper(input[i]);
            }
        } else {
            output[j] = input[i];
        }
        
        i++;
        j++;
    }
    output[j] = '\0';

    return output;
}

int main() {
    char input[100];
    printf("Enter a snake_case string: ");
    fgets(input, sizeof(input), stdin);

    input[strlen(input) - 1] = '\0'; 

    char *result = snakeToCamel(input);
    
    if(result != NULL) {
        printf("CamelCase string is: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failure\n");
    }

    return 0;
}