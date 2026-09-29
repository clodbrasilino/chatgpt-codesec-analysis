#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* removeLowercase(const char* input) {
    int len = strlen(input);
    char *output = (char*)malloc(len + 1);
    if (output == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (!islower(input[i])) {
            output[j] = input[i];
            j++;
        }
    }
    output[j] = '\0';

    return output;
}

int main() {
    const char* str1 = "Hello Test";
    char* result = removeLowercase(str1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}