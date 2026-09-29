#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* move_numbers(char *str) {
    int len = strlen(str);
    char *numStr = (char *)malloc(len + 1);
    if (numStr == NULL) {
        return NULL;
    }
    int numIndex = 0;

    for (int i = 0, j = 0; i < len; ++i) {
        if (isdigit(str[i])) {
            numStr[numIndex++] = str[i];
        } else {
            str[j++] = str[i];
        }
    }
    --numIndex;
    for (int k = len - 1; numIndex >= 0; --k, --numIndex) {
        str[k] = numStr[numIndex];
    }
    str[len] = '\0';
    free(numStr);
    return str;
}

int main() {
    char str[] = "Hello123World456";
    char *result = move_numbers(str);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}