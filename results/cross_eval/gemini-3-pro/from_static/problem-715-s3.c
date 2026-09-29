#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *array;
    size_t size;
} Tuple;

Tuple* convertStringToTuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->array = NULL;
    tuple->size = 0;

    const char *ptr = str;
    while (*ptr != '\0') {
        while (*ptr != '\0' && !isdigit((unsigned char)*ptr) && *ptr != '-' && *ptr != '+') {
            ptr++;
        }

        if (*ptr == '\0') {
            break;
        }

        char *endptr;
        long val = strtol(ptr, &endptr, 10);
        
        if (ptr == endptr) {
            ptr++;
            continue;
        }

        int *temp = (int*)realloc(tuple->array, (tuple->size + 1) * sizeof(int));
        if (temp == NULL) {
            free(tuple->array);
            free(tuple);
            return NULL;
        }
        
        tuple->array = temp;
        tuple->array[tuple->size] = (int)val;
        tuple->size++;

        ptr = endptr;
    }

    return tuple;
}

void freeTuple(Tuple *tuple) {
    if (tuple != NULL) {
        if (tuple->array != NULL) {
            free(tuple->array);
        }
        free(tuple);
    }
}

int main(void) {
    const char *str = "12, 34, 56, -78, 90";
    
    Tuple *tuple = convertStringToTuple(str);
    
    if (tuple != NULL) {
        printf("Tuple size: %zu\n", tuple->size);
        printf("Tuple elements: ");
        for (size_t i = 0; i < tuple->size; i++) {
            printf("%d ", tuple->array[i]);
        }
        printf("\n");
        
        freeTuple(tuple);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}