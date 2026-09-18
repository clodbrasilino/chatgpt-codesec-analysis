#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** convert_tuple_to_list(char* tuple[], int size, char* str) {
    int strSize = strlen(str);
    char** list = malloc(sizeof(char*) * size * 2);

    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list[i*2] = tuple[i];
        list[i*2 + 1] = malloc(strSize + 1);
        strcpy(list[i*2 + 1], str);
    }
    
    return list;
}

void free_list(char** list, int size, char* str) {
    for(int i = 0; i < size; i++) {
        if(i%2 != 0) {
            free(list[i]);
        }
    }
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    free(list);
}

int main() {
    char* tuple[] = {"element1", "element2", "element3"};
    int size = sizeof(tuple) / sizeof(char*);
    
    char* str = "addedString";
    
    char** list = convert_tuple_to_list(tuple, size, str);
    
    for(int i = 0; i < size * 2; i++) {
        printf("%s ", list[i]);
    }
    printf("\n");
    
    free_list(list, size * 2, str);
    
    return 0;
}