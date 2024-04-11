#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** extractValues(char* str) {
    int i = 0;
    int count = 0;
    char** result = (char**)malloc(sizeof(char*) * strlen(str));

    if (result == NULL) return NULL;

    char* token = strtok(str, "\"");
    while (token != NULL) {
       if (count % 2 != 0) {
            result[i] = (char*)malloc(sizeof(char) * strlen(token) + 1);
            
            if (result[i] == NULL) {
                for (int j = 0; j < i; j++) free(result[j]);
                free(result);
                return NULL;
            }

            strcpy(result[i], token);
            i++;
        }
        token = strtok(NULL, "\"");
        count++;
    }
    
    result[i] = NULL;
    return result;
}

int main() {
    char str[] = "This is a \"test\" string with \"multiple\" values \"in quotes\".";
    char** values = extractValues(str);

    if (values != NULL) {
        for (int i = 0; values[i] != NULL; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }

    return 0;
}