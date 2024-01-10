#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LENGTH 100

typedef struct {
    int* values;
    int size;
} Tuple;

Tuple convertStringToTuple(const char* str) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    char* copy = malloc(strlen(str) + 1);
    if (!copy) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(copy, str);
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length = strlen(copy);
    int* values = calloc(length, sizeof(int));
    if (!values) {
        fprintf(stderr, "Memory allocation error\n");
        free(copy);
        exit(1);
    }

    int size = 0;
    char* token = strtok(copy, " ");
    while (token != NULL && size < length) {
        char* end;
        long val = strtol(token, &end, 10);
        if (end == token || *end != '\0' || (val > INT_MAX || val < INT_MIN)) {
            fprintf(stderr, "Number out of range\n");
            free(values);
            free(copy);
            exit(1);
        }
        values[size++] = (int)val;
        token = strtok(NULL, " ");
    }
  
    Tuple tuple;
    tuple.values = values;
    tuple.size = size;

    free(copy);

    return tuple;
}

int main() {
    const char* str = "5 10 15 20";
    Tuple tuple = convertStringToTuple(str);
    
    printf("Tuple: ");
    for (int i = 0; i < tuple.size; i++) {
        printf("%d ", tuple.values[i]);
    }
    printf("\n");

    free(tuple.values);

    return 0;
}