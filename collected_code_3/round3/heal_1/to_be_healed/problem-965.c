#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camelToSnake(char* input) {
    int i = 0, j = 0;
    char* output = (char*)malloc(sizeof(char) * 100);

    while (input[i]) {
        if (isupper(input[i])) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'output' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            output[j] = '_';
            j++;
            output[j] = tolower(input[i]);
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'output' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            output[j] = input[i];
        }
        i++;
        j++;
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'output' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
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