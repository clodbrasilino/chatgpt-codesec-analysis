#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** convert_tuple_to_list(char* tuple[], int size, char* str) {
    int strSize = strlen(str);
    char** list = (char**) malloc(sizeof(char*) * size * 2);

    if(list == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        list[i*2] = strdup(tuple[i]);
        list[i*2 + 1] = strdup(str);
        if(list[i*2] == NULL || list[i*2 + 1] == NULL)
        {
            for(int j = 0; j < i*2; j++) {
               free(list[j]);
            }
            /* Possible weaknesses found:
             *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            free(list);
            return NULL;
        }
    }
    return list;
}

void free_list(char** list, int size) {
    for(int i = 0; i < size; i++) {
        free(list[i]);
    }
    free(list);
}

int main() {
    char* tuple[] = {"element1", "element2", "element3"};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    char* str = "addedString";

    char** list = convert_tuple_to_list(tuple, size, str);
    if(list == NULL)
    {
        return 1;
    }

    for(int i = 0; i < size*2; i++) {
        printf("%s ", list[i]);
    }
    printf("\n");

    free_list(list, size*2);

    return 0;
}