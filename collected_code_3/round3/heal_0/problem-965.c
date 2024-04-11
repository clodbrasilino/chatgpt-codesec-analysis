#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camelToSnake(char* input) {
    int i = 0, j = 0;
    char* output = (char*)malloc(sizeof(char) * 100);

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
    scanf("%s", input);
    char* output = camelToSnake(input);
    printf("The snake_case string is: %s\n", output);
    free(output);
    return 0;
}