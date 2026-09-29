#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <regex.h>

char *convertToSnakeCase(const char *camelCase) {
    if (camelCase == NULL) {
        return NULL;
    }

    int len = strlen(camelCase);
    char *snakeCase = malloc(2 * len);
    if (snakeCase == NULL) {
        return NULL;
    }

    int i, j = 0;
    for (i = 0; i < len; ++i) {
        if (isupper(camelCase[i]) && i > 0) {
            snakeCase[j++] = '_';
        }
        snakeCase[j++] = tolower(camelCase[i]);
    }

    snakeCase[j] = '\0';
    return snakeCase;
}

int main() {
    const char *camelCase = "camelCaseString";
    char *snakeCase = convertToSnakeCase(camelCase);

    if (snakeCase) {
        printf("SnakeCase: %s\n", snakeCase);
        free(snakeCase);
    }

    return 0;
}
