#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char keys[MAX_SIZE][MAX_SIZE];
    char values[MAX_SIZE][MAX_SIZE];
    int size;
} Dictionary;

void dropEmptyItems(Dictionary *dict) {
    int i, j = 0;
    Dictionary temp;

    temp.size = 0;

    for(i = 0; i < dict->size; i++) {
        if(strlen(dict->values[i]) != 0) {
            strcpy(temp.keys[j], dict->keys[i]);
            strcpy(temp.values[j], dict->values[i]);
            temp.size++;
            j++;
        }
    }

    for(i = 0; i < temp.size; i++) {
        strcpy(dict->keys[i], temp.keys[i]);
        strcpy(dict->values[i], temp.values[i]);
    }

    dict->size = temp.size;
}

int main() {
    Dictionary dict = {{"key1", "key2", "key3", "key4"}, {"value1", "", "value3", ""}, 4};

    dropEmptyItems(&dict);

    for(int i = 0; i < dict.size; i++) {
        printf("%s: %s\n", dict.keys[i], dict.values[i]);
    }

    return 0;
}