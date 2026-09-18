#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dict {
    char* key;
    int value;
} Dict;

Dict* filterDict(Dict* dict, int len, int filterValue, int* newLen) {
    Dict* filteredDict = (Dict*)malloc(sizeof(Dict)*len);
    *newLen = 0;
    for(int i=0; i<len; i++) {
        if(dict[i].value >= filterValue) {
            /* Possible weaknesses found:
             *  write of 8 bytes to beyond the end of the region
             *  dereference of possibly-NULL 'filteredDict' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             */
            filteredDict[*newLen].key = (char*)malloc(strlen(dict[i].key)+1);
            strcpy(filteredDict[*newLen].key, dict[i].key);
            filteredDict[*newLen].value = dict[i].value;
            (*newLen)++;
        }
    }
    
    filteredDict = realloc(filteredDict, sizeof(Dict)**newLen);
    
    return filteredDict;
}

int main() {
    int len = 4;
    Dict dict[4] = {{"key1", 4}, {"key2", 2}, {"key3", 5}, {"key4", 3}};
    
    for(int i=0; i<len; i++) {
        dict[i].key = (char*)malloc(strlen(dict[i].key)+1);
        strcpy(dict[i].key, dict[i].key);
    }
    
    int newLen;
    Dict* filteredDict = filterDict(dict, len, 3, &newLen);
    
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

    return 0;
}