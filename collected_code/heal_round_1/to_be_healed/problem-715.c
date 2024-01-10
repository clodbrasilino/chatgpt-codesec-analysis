#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* values;
    int size;
} Tuple;

Tuple convertStringToTuple(const char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(str);
    int* values = malloc(length * sizeof(int));
    int size = 0;
    
    char* token = strtok((char*)str, " ");
    while (token != NULL) {
        /* Possible weaknesses found:
         *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
         *  dereference of possibly-NULL 'values' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        values[size++] = atoi(token);
        token = strtok(NULL, " ");
    }
    
    Tuple tuple;
    tuple.values = values;
    tuple.size = size;
    
    return tuple;
}

int main() {
    const char* str = "5 10 15 20";
    Tuple tuple = convertStringToTuple(str);
    
    printf("Tuple: ");
    for (int i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.values[i]);
    }
    
    free(tuple.values);
    
    return 0;
}