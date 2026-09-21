#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *array;
    size_t size;
} Tuple;

Tuple* convertStringToIntTuple(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    size_t count = 0;
    const char* ptr = str;
    while (*ptr != '\0') {
        while (*ptr != '\0' && !isdigit(*ptr) && *ptr != '-' && *ptr != '+') {
            ptr++;
        }
        if (*ptr != '\0') {
            count++;
            while (*ptr != '\0' && (isdigit(*ptr) || *ptr == '-' || *ptr == '+')) {
                ptr++;
            }
        }
    }

    tuple->array = (int*)malloc(count * sizeof(int));
    if (tuple->array == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->size = count;

    ptr = str;
    size_t i = 0;
    while (*ptr != '\0') {
        while (*ptr != '\0' && !isdigit(*ptr) && *ptr != '-' && *ptr != '+') {
            ptr++;
        }
        if (*ptr != '\0') {
            /* Possible weaknesses found:
             * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
             */
            tuple->array[i++] = atoi(ptr);
            while (*ptr != '\0' && (isdigit(*ptr) || *ptr == '-' || *ptr == '+')) {
                ptr++;
            }
        }
    }

    return tuple;
}

void freeTuple(Tuple* tuple) {
    if (tuple != NULL) {
        if (tuple->array != NULL) {
            free(tuple->array);
        }
        free(tuple);
    }
}

int main() {
    const char* str = "12, 34, 56, -78, 90";
    
    Tuple* tuple = convertStringToIntTuple(str);
    
    if (tuple != NULL) {
        printf("(");
        for (size_t i = 0; i < tuple->size; i++) {
            printf("%d", tuple->array[i]);
            if (i < tuple->size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
        
        freeTuple(tuple);
    }
    
    return 0;
}