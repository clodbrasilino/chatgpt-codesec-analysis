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
    numStr[0] = '\0';

    char *nonNumStr = (char *)malloc(len + 1);
    if (nonNumStr == NULL) {
        free(numStr);
        return NULL;
    }
    nonNumStr[0] = '\0';

    for (int i = 0; i < len; ++i) {
        if (isdigit(str[i])) {
            strncat(numStr, &str[i], 1);
        } else {
            strncat(nonNumStr, &str[i], 1);
        }
    }

    snprintf(str, len + 1, "%s%s", nonNumStr, numStr);

    free(numStr);
    free(nonNumStr);
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