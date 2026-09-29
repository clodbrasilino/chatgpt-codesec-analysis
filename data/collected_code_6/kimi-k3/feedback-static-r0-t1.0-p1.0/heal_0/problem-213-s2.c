#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    size_t count;
} StringTuple;

StringTuple* concatenate_tuples(const StringTuple *tuple1, const StringTuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return NULL;
    }

    StringTuple *result = malloc(sizeof(StringTuple));
    if (result == NULL) {
        return NULL;
    }

    result->count = tuple1->count + tuple2->count;
    result->strings = malloc(result->count * sizeof(char *));
    if (result->strings == NULL) {
        free(result);
        return NULL;
    }

    size_t i;
    for (i = 0; i < tuple1->count; i++) {
        result->strings[i] = malloc(strlen(tuple1->strings[i]) + 1);
        if (result->strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result->strings[j]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        strcpy(result->strings[i], tuple1->strings[i]);
    }

    for (i = 0; i < tuple2->count; i++) {
        result->strings[tuple1->count + i] = malloc(strlen(tuple2->strings[i]) + 1);
        if (result->strings[tuple1->count + i] == NULL) {
            for (size_t j = 0; j < tuple1->count + i; j++) {
                free(result->strings[j]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        strcpy(result->strings[tuple1->count + i], tuple2->strings[i]);
    }

    return result;
}

void free_tuple(StringTuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->strings[i]);
    }
    free(tuple->strings);
    free(tuple);
}

void print_tuple(const StringTuple *tuple) {
    if (tuple == NULL) {
        printf("NULL tuple\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("\"%s\"", tuple->strings[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    char *strings1[] = {"Hello", "World"};
    char *strings2[] = {"Foo", "Bar", "Baz"};

    StringTuple tuple1;
    tuple1.strings = strings1;
    tuple1.count = 2;

    StringTuple tuple2;
    tuple2.strings = strings2;
    tuple2.count = 3;

    printf("Tuple 1: ");
    print_tuple(&tuple1);

    printf("Tuple 2: ");
    print_tuple(&tuple2);

    StringTuple *result = concatenate_tuples(&tuple1, &tuple2);
    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate tuples\n");
        return EXIT_FAILURE;
    }

    printf("Concatenated: ");
    print_tuple(result);

    free_tuple(result);

    return EXIT_SUCCESS;
}