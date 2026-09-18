#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct KeyValue {
    char* key;
    char* value;
} KeyValue;

KeyValue* tupleToDict(char** tuple, int size) {
    if(tuple == NULL || size < 2 || (size % 2 != 0)) {
        return NULL;
    }

    KeyValue* dict = malloc(sizeof(KeyValue) * (size/2));

    if(dict == NULL) {
        return NULL;
    }

    for(int i=0; i<size; i+=2) {
        dict[i/2].key = malloc(strlen(tuple[i])+1);
        dict[i/2].value = malloc(strlen(tuple[i+1])+1);
        
        if(dict[i/2].key == NULL || dict[i/2].value == NULL) {
            free(dict);
            return NULL;
        }
        
        strcpy(dict[i/2].key, tuple[i]);
        strcpy(dict[i/2].value, tuple[i+1]);
    }

    return dict;
}

void freeDict(KeyValue* dict, int size) {
    if(dict == NULL) {
        return;
    }
    
    for(int i=0; i<size; ++i) {
        free(dict[i].key);
        free(dict[i].value);
    }
    
    free(dict);
}

int main() {
    char* tuple[] = {"one", "1", "two", "2", "three", "3"};
    int size = sizeof(tuple)/sizeof(tuple[0]);
    
    KeyValue* dict = tupleToDict(tuple, size);
    
    if(dict == NULL) {
        printf("Dictionary creation failed\n");
        return EXIT_FAILURE;
    }
    
    for(int i=0; i<(size/2); ++i) {
        printf("Key: %s\tValue: %s\n", dict[i].key, dict[i].value);
    }
    
    freeDict(dict, size/2);
    
    return EXIT_SUCCESS;
}