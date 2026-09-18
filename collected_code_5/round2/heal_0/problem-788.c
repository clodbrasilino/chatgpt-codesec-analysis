#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    char *string;
    Node *list;
} Tuple;

Tuple* create_tuple(const char *str, Node *list) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if(tuple == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    tuple->string = malloc(strlen(str) + 1);
    if(tuple->string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(tuple);
        return NULL;
    }

    strcpy(tuple->string, str);
    tuple->list = list;

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if(tuple == NULL) {
        return;
    }

    free(tuple->string);
    free(tuple);
}

int main() {
    Node *list = malloc(sizeof(Node));
    list->value = 1;
    list->next = NULL;

    Tuple *tuple = create_tuple("Example", list);
    if(tuple == NULL) {
        fprintf(stderr, "Tuple creation failed\n");
        return 1;
    }

    printf("Tuple created: %s\n", tuple->string);

    free_tuple(tuple);
    free(list);

    return 0;
}