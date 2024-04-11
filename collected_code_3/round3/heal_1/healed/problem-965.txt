#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camelToSnake(char* input) {
    int i = 0, j = 0;
    char* output = (char*)malloc(sizeof(char) * 100);

    if (output == NULL) {
        fprintf(stderr, "malloc failed");
        return NULL;
    }

    while (input[i]) {
        if (isupper(input[i])) {
            output[j] = '_';
            j++;
            output[j] = tolower(input[i]);
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

    printf("Enter a camelCase string: ");
    if (scanf("%s", input) != 1) {
        fprintf(stderr, "scanf failed");
        return 1;
    }

    char* output = camelToSnake(input);

    if (output == NULL) {
        return 1;
    }

    printf("The snake_case string is: %s\n", output);
    free(output);
    return 0;
}