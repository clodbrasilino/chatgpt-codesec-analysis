#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int integer;
    double decimal;
    char character;
} Tuple;

Tuple* createTuple(int integer, double decimal, char character) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    tuple->integer = integer;
    tuple->decimal = decimal;
    tuple->character = character;
    return tuple;
}

void removeInteger(Tuple *tuple) {
    if (!tuple) {
        fprintf(stderr, "Error: tuple pointer is NULL\n");
        return;
    }
    tuple->integer = 0;
}

void removeDecimal(Tuple *tuple) {
    if (!tuple) {
        fprintf(stderr, "Error: tuple pointer is NULL\n");
        return;
    }
    tuple->decimal = 0.0;
}

void removeCharacter(Tuple *tuple) {
    if (!tuple) {
        fprintf(stderr, "Error: tuple pointer is NULL\n");
        return;
    }
    tuple->character = '\0';
}

void displayTuple(Tuple *tuple) {
    if (!tuple) {
        fprintf(stderr, "Error: tuple pointer is NULL\n");
        return;
    }
    printf("Integer: %d\nDecimal: %.2lf\nCharacter: %c\n\n", tuple->integer, tuple->decimal, tuple->character);
}

int main() {
    Tuple *tuple = createTuple(5, 3.14, 'A');
    displayTuple(tuple);

    printf("Removing decimal...\n");
    removeDecimal(tuple);
    displayTuple(tuple);

    printf("Removing character...\n");
    removeCharacter(tuple);
    displayTuple(tuple);

    free(tuple);
    return 0;
}