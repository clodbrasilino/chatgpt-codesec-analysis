#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    double value;
} Tuple;

char *tuple_to_string(const Tuple *tuple) {
    if (tuple == NULL) {
        return NULL;
    }

    int required_length = snprintf(NULL, 0, "(%d, %.49s, %.2f)",
                                    tuple->id, tuple->name, tuple->value);

    if (required_length < 0) {
        return NULL;
    }

    char *result = (char *)malloc((size_t)required_length + 1);
    if (result == NULL) {
        return NULL;
    }

    int written = snprintf(result, (size_t)required_length + 1, "(%d, %.49s, %.2f)",
                           tuple->id, tuple->name, tuple->value);

    if (written < 0 || written >= required_length + 1) {
        free(result);
        return NULL;
    }

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