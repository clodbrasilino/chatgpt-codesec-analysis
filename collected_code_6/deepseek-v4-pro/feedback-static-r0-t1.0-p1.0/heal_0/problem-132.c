#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    double value;
} Tuple;

char *tuple_to_string(const Tuple *tuple) {
    if (tuple == NULL) {
        return NULL;
    }

    char buffer[256];
    int required_length = snprintf(buffer, sizeof(buffer), "(%d, %s, %.2f)",
                                    tuple->id, tuple->name, tuple->value);

    if (required_length < 0) {
        return NULL;
    }

    char *result = (char *)malloc((size_t)required_length + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, buffer, (size_t)required_length);
    result[required_length] = '\0';

    return result;
}

int main(void) {
    Tuple tuple = {1, "example", 3.14159};
    char *str = tuple_to_string(&tuple);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    } else {
        printf("Error: Failed to convert tuple to string.\n");
        return 1;
    }

    return 0;
}