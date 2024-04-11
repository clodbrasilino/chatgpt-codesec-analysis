#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** extractValues(char* str) {
    int i = 0;
    int count = 0;
    char** result = (char**)malloc(sizeof(char*) * strlen(str));

    char* token = strtok(str, "\"");
    while (token != NULL) {
        if (count % 2 != 0) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[i] = (char*)malloc(sizeof(char) * strlen(token) + 1);
            strcpy(result[i], token);
            i++;
        }
        token = strtok(NULL, "\"");
        count++;
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    result[i] = NULL;
    return result;
}

int main() {
    char str[] = "This is a \"test\" string with \"multiple\" values \"in quotes\".";
    char** values = extractValues(str);

    for (int i = 0; values[i] != NULL; i++) {
        printf("%s\n", values[i]);
        free(values[i]);
    }
    free(values);

    return 0;
}