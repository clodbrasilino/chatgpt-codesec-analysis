#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dict {
    char* key;
    int value;
} Dict;

Dict* filterDict(Dict* dict, int len, int filterValue, int* newLen) {
    int filteredCount = 0;
    for(int i = 0; i < len; i++) {
        if(dict[i].value >= filterValue) {
            filteredCount++;
        }
    }
   
    Dict* filteredDict = (Dict*)malloc(sizeof(Dict) * filteredCount);
    if(!filteredDict) {
        return NULL;
    }

    *newLen = 0;
    for(int i=0; i<len; i++) {
        if(dict[i].value >= filterValue) {
            filteredDict[*newLen].key = (char*)malloc(strlen(dict[i].key)+1);
            if(!filteredDict[*newLen].key){
                return NULL;
            }

            strcpy(filteredDict[*newLen].key, dict[i].key);
            filteredDict[*newLen].value = dict[i].value;
            (*newLen)++;
        }
    }

    return filteredDict;
}

int main() {
    int len = 4;
    Dict dict[4] = {{"key1", 4}, {"key2", 2}, {"key3", 5}, {"key4", 3}};

    for(int i=0; i<len; i++) {
        char* oldKey = dict[i].key;
        dict[i].key = (char*)malloc(strlen(oldKey)+1);
        strcpy(dict[i].key, oldKey);
    }

    int newLen;
    Dict* filteredDict = filterDict(dict, len, 3, &newLen);

    if(!filteredDict){
        return EXIT_FAILURE;
    }

    for(int i=0; i<newLen; i++) {
       printf("Key: %s, Value: %d\n", filteredDict[i].key, filteredDict[i].value);
    }

    for(int i=0; i<newLen; i++) {
        free(filteredDict[i].key);
    }

    free(filteredDict);

    for(int i=0; i<len; i++) {
        free(dict[i].key);
    }

    return EXIT_SUCCESS;
}