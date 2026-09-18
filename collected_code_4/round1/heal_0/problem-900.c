#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int prependNumberToString(int num, char *strOrig, char **strNew) {
    if (strOrig == NULL || strNew == NULL) {
        return -1;
    }
    int length = snprintf(NULL, 0, "%d", num);
    *strNew = malloc(length + strlen(strOrig) + 1);
    if (*strNew == NULL) {
        return -1;
    }
    sprintf(*strNew, "%d%s", num, strOrig);
    return 0;
}

int main() {
    char *strOrig = "Hello World!";
    char *strNew = NULL;
    int result = prependNumberToString(123, strOrig, &strNew);
    if (result == 0) {
        printf("%s\n", strNew);
        free(strNew);
    } else {
        printf("Error occurred\n");
    }
    return 0;
}