#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char *item;
    char *value;
} Tuple;

typedef struct Record {
    Tuple *tuples;
    int count;
} Record;

void removeTuple(Record *record, const char *remItem) {
    if(record == NULL || remItem == NULL) return;
    
    for (int i = 0; i < record->count; i++) {
        if (strcmp((record->tuples + i)->item, remItem) == 0) {
            for (int j = i; j < record->count - 1; ++j) {
                *(record->tuples + j) = *(record->tuples + j + 1);
            }
            --record->count;
            return;
        }
    }
}

int main() {
    Record record;
    record.count = 3;
    record.tuples = (Tuple*) malloc(sizeof(Tuple) * record.count);
    
    if(record.tuples == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    
    for(int i = 0; i < record.count; i++)
    {
        (record.tuples + i)->item = (char*) malloc(sizeof(char) * 20);
        (record.tuples + i)->value = (char*) malloc(sizeof(char) * 20);
        if((record.tuples + i)->item == NULL || (record.tuples + i)->value == NULL) {
            printf("Memory not allocated.\n");
            exit(0);
        }

        sprintf((record.tuples + i)->item, "Item%d", i + 1);
        sprintf((record.tuples + i)->value, "Value%d", i + 1);
    }
    
    const char remove_item[] = "Item2";
    removeTuple(&record, remove_item);
    
    for(int i = 0; i < record.count; i++)
    {
        printf("Tuple %d Item: %s Value: %s\n", i + 1, (record.tuples+i)->item, (record.tuples+i)->value);
        free((record.tuples + i)->item);
        free((record.tuples + i)->value);
    }

    free(record.tuples);

    return 0;
}