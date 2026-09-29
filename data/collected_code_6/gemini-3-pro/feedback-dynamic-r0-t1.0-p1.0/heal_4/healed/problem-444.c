#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

TupleList* trimTuples(const TupleList *inputList, size_t k) {
    if (!inputList || !inputList->tuples) {
        return NULL;
    }

    TupleList *resultList = malloc(sizeof(TupleList));
    if (!resultList) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < inputList->count; i++) {
        if (inputList->tuples[i].size != k) {
            count++;
        }
    }

    resultList->count = count;
    if (count == 0) {
        resultList->tuples = NULL;
        return resultList;
    }

    resultList->tuples = malloc(count * sizeof(Tuple));
    if (!resultList->tuples) {
        free(resultList);
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < inputList->count; i++) {
        if (inputList->tuples[i].size != k) {
            Tuple *current = &inputList->tuples[i];
            Tuple *result = &resultList->tuples[idx++];
            
            result->size = current->size;
            if (result->size > 0) {
                result->elements = malloc(result->size * sizeof(int));
                if (!result->elements) {
                    for (size_t j = 0; j < idx - 1; j++) {
                        free(resultList->tuples[j].elements);
                    }
                    free(resultList->tuples);
                    free(resultList);
                    return NULL;
                }
                for (size_t j = 0; j < result->size; j++) {
                    result->elements[j] = current->elements[j];
                }
            } else {
                result->elements = NULL;
            }
        }
    }

    return resultList;
}

void freeTupleList(TupleList *list) {
    if (list) {
        if (list->tuples) {
            for (size_t i = 0; i < list->count; i++) {
                free(list->tuples[i].elements);
            }
            free(list->tuples);
        }
        free(list);
    }
}

void printTupleList(const TupleList *list) {
    if (!list) return;
    printf("[");
    for (size_t i = 0; i < list->count; i++) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        if (list->tuples[i].size == 1) {
            printf(",");
        }
        printf(")");
        if (i < list->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    size_t capacity = 1024;
    char *buffer = malloc(capacity);
    if (!buffer) return 1;
    
    size_t len = 0;
    size_t read_bytes;
    while ((read_bytes = fread(buffer + len, 1, capacity - len - 1, stdin)) > 0) {
        len += read_bytes;
        if (len >= capacity - 1) {
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
        }
    }
    if (len == 0) {
        free(buffer);
        return 0;
    }
    buffer[len] = '\0';
    
    char *end_bracket = strrchr(buffer, ']');
    size_t k = 0;
    if (end_bracket != NULL) {
        char *k_str = end_bracket + 1;
        while (*k_str) {
            if (isdigit((unsigned char)*k_str)) {
                k = strtoul(k_str, NULL, 10);
                break;
            }
            k_str++;
        }
    } else {
        end_bracket = buffer + len;
    }
    
    TupleList inputList;
    inputList.count = 0;
    size_t tupleCapacity = 1024;
    inputList.tuples = malloc(tupleCapacity * sizeof(Tuple));
    
    char *ptr = buffer;
    while ((ptr = strchr(ptr, '(')) != NULL && ptr < end_bracket) {
        ptr++;
        
        if (inputList.count >= tupleCapacity) {
            tupleCapacity *= 2;
            inputList.tuples = realloc(inputList.tuples, tupleCapacity * sizeof(Tuple));
        }
        
        inputList.tuples[inputList.count].size = 0;
        size_t elementsCapacity = 16;
        inputList.tuples[inputList.count].elements = malloc(elementsCapacity * sizeof(int));
        
        while (*ptr && *ptr != ')') {
            if (isdigit((unsigned char)*ptr) || *ptr == '-') {
                if (inputList.tuples[inputList.count].size >= elementsCapacity) {
                    elementsCapacity *= 2;
                    inputList.tuples[inputList.count].elements = realloc(
                        inputList.tuples[inputList.count].elements,
                        elementsCapacity * sizeof(int)
                    );
                }
                inputList.tuples[inputList.count].elements[inputList.tuples[inputList.count].size++] = strtol(ptr, &ptr, 10);
            } else {
                ptr++;
            }
        }
        inputList.count++;
    }
    
    TupleList *trimmed = trimTuples(&inputList, k);
    printTupleList(trimmed);
    
    freeTupleList(trimmed);
    for (size_t i = 0; i < inputList.count; i++) {
        free(inputList.tuples[i].elements);
    }
    free(inputList.tuples);
    free(buffer);
    
    return 0;
}