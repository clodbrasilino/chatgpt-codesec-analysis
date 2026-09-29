#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int size, int len, int *newSize) {
    char **newStrings = (char **)calloc(size, sizeof(char *));
    if(!newStrings) {
        return NULL;
    }

    *newSize = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        if (strlen(strings[i]) == len) {
            char *temp = (char *)calloc(len + 1, sizeof(char));
            if (!temp) {
                for(int j = 0; j < *newSize; j++){
                    free(newStrings[j]);
                }
                free(newStrings);
                return NULL;
            }
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(temp, strings[i], len);
            temp[len] = '\0';

            if(*newSize < size){
                newStrings[*newSize] = temp;
                (*newSize)++;
            }else{
                free(temp);
            }
        }
    }

    char **temp = (char **)realloc(newStrings, sizeof(char *) * (*newSize));
    if(!temp){
        for(int j = 0; j<*newSize; j++){
            free(newStrings[j]);
        }
        free(newStrings);
        return NULL;
    }
    newStrings = temp;
    return newStrings;
}

int main() {
    char *strings[] = {"hello", "world", "C", "developer", "code"};
    int size = sizeof(strings) / sizeof(strings[0]);
    int newSize = 0;
    char **newStrings = extractStrings(strings, size, 5, &newSize);

    if(newStrings == NULL){
        return 1;
    }

    for (int i = 0; i < newSize; i++) {
        printf("%s\n", newStrings[i]);
        free(newStrings[i]);
    }

    free(newStrings);
    return 0;
}