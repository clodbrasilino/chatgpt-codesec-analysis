#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** elements;
    int size;
} Tuple;

Tuple* string_to_tuple(const char* input) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    const char* delimiter = ",";
    char* input_copy = strdup(input);
    if (input_copy == NULL) {
        free(tuple);
        return NULL;
    }

    int count = 0;
    for (const char* p = input; *p; p++) {
        if (*p == *delimiter) {
            count++;
        }
    }
    count++;  // Include the last token

    tuple->size = count;
    if (count == 0) {
        free(input_copy);
        free(tuple);
        return NULL;
    }

    tuple->elements = (char**)malloc(tuple->size * sizeof(char*));
    if (tuple->elements == NULL) {
        free(input_copy);
        free(tuple);
        return NULL;
    }

    const char* start = input;
    for (int i = 0; i < tuple->size; i++) {
        const char* end = strchr(start, *delimiter);
        if (end) {
            int len = end - start;
            tuple->elements[i] = (char*)malloc(len + 1);
            if (tuple->elements[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(tuple->elements[j]);
                }
                free(tuple->elements);
                free(input_copy);
                free(tuple);
                return NULL;
            }
            strncpy(tuple->elements[i], start, len);
            tuple->elements[i][len] = '\0';
            start = end + 1;
        } else {
            tuple->elements[i] = strdup(start);
            if (tuple->elements[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(tuple->elements[j]);
                }
                free(tuple->elements);
                free(input_copy);
                free(tuple);
                return NULL;
            }
        }
    }

    free(input_copy);
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple) {
        for (int i = 0; i < tuple->size; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main() {
    const char* input1 = "python3.0";
    const char* input2 = "item1";
    const char* input3 = "15.10";

    Tuple* result1 = string_to_tuple(input1);
    Tuple* result2 = string_to_tuple(input2);
    Tuple* result3 = string_to_tuple(input3);

    if (result1) {
        for (int i = 0; i < result1->size; i++) {
            printf("%s\n", result1->elements[i]);
        }
        free_tuple(result1);
    } else {
        printf("Failed to create tuple for input1.\n");
    }

    if (result2) {
        for (int i = 0; i < result2->size; i++) {
            printf("%s\n", result2->elements[i]);
        }
        free_tuple(result2);
    } else {
        printf("Failed to create tuple for input2.\n");
    }

    if (result3) {
        for (int i = 0; i < result3->size; i++) {
            printf("%s\n", result3->elements[i]);
        }
        free_tuple(result3);
    } else {
        printf("Failed to create tuple for input3.\n");
    }

    return 0;
}