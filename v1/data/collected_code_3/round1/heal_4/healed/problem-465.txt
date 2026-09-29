#include <stdio.h>
#include <string.h>

#define MAX_DICT_SIZE 100
#define MAX_STR_SIZE 100

typedef struct {
    char key[MAX_STR_SIZE];
    char value[MAX_STR_SIZE];
} DictItem;

void dropEmptyItems(DictItem* dict, int* size) {
    int i = 0;
    while (i < *size) {
        if (strcmp(dict[i].value, "") == 0) {
            for (int j = i; j < *size - 1; j++) {
                dict[j] = dict[j + 1];
            }
            DictItem emptyItem;
            strcpy(emptyItem.key, "");
            strcpy(emptyItem.value, "");
            dict[*size - 1] = emptyItem;
            (*size)--;
        } else {
            i++;
        }
    }
}

int main() {
    DictItem dict[MAX_DICT_SIZE] = {
        {"key1", "value1"},
        {"key2", ""},
        {"key3", "value3"},
        {"key4", ""},
        {"key5", "value5"}
    };
    int size = 5;

    dropEmptyItems(dict, &size);

    for (int i = 0; i < size; i++) {
        printf("Key: %s, Value: %s\n", dict[i].key, dict[i].value);
    }

    return 0;
}