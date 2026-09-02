#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float value;
} FloatTuple;

FloatTuple* stringToFloatTuple(const char *str) {
    FloatTuple *tuple = (FloatTuple *)malloc(sizeof(FloatTuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->value = strtof(str, NULL);
    return tuple;
}

int main() {
    const char *input = "123.456";
    FloatTuple *result = stringToFloatTuple(input);
    if (result != NULL) {
        printf("%.3f\n", result->value);
        free(result);
    } else {
        fprintf(stderr, "Failed to allocate memory\n");
    }
    return 0;
}