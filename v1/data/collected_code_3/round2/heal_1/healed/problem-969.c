#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

Tuple* joinTuples(Tuple *tuples, int size, int *newSize) {
    Tuple *result = (Tuple*)malloc(sizeof(Tuple) * size);
    if(!result) return NULL;

    int count = 0;

    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(strcmp(tuples[i].first, tuples[j].first) == 0) {
                Tuple newTuple;
                newTuple.first = tuples[i].first;

                size_t len = strlen(tuples[i].second) + strlen(tuples[j].second) + 1;
                newTuple.second = (char*)malloc(len);
                if(!newTuple.second) {
                    for(int k=0; k<count; k++) {
                        free(result[k].second);
                    }
                    free(result);
                    return NULL;
                }
               
                strcpy(newTuple.second, tuples[i].second);
                strcat(newTuple.second, tuples[j].second);

                result[count++] = newTuple;
                i = j;
            }
        }
    }

    *newSize = count;
    return result;
}

int main() {
    int size = 3;
    Tuple tuples[3] = {
        {"apple", "red"},
        {"apple", "green"},
        {"banana", "yellow"}
    };

    int newSize;
    Tuple *result = joinTuples(tuples, size, &newSize);

    if(result){
        for(int i = 0; i < newSize; i++) {
            printf("%s, %s\n", result[i].first, result[i].second);
            free(result[i].second);
        }
        free(result);
    }

    return 0;
}