#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { INT, STRING } Type;

typedef struct {
    union {
        int asInt;
        char *asString;
    };
    Type type;
} Mixed;

int compareMixed(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'ma' can be declared as pointer to const [constVariablePointer]
     */
    Mixed *ma = (Mixed *)a;
    /* Possible weaknesses found:
     *  Variable 'mb' can be declared as pointer to const [constVariablePointer]
     */
    Mixed *mb = (Mixed *)b;

    if (ma->type == INT && mb->type == INT) {
        return ma->asInt - mb->asInt;
    }
    if (ma->type == STRING && mb->type == STRING) {
        return strcmp(ma->asString, mb->asString);
    }
    if (ma->type == INT) {
        return -1;
    }
    return 1;
}

void freeMixed(Mixed *mixed, int size) {
    for (int i = 0; i < size; i++) {
        if (mixed[i].type == STRING) {
            free(mixed[i].asString);
        }
    }
    free(mixed);
}

int main() {
    Mixed mixed[] = {
        { .asInt = 3, .type = INT },
        { .asString = "apple", .type = STRING },
        { .asInt = 1, .type = INT },
        { .asString = "banana", .type = STRING },
        { .asInt = 2, .type = INT },
        { .asString = "cherry", .type = STRING }
    };

    int size = sizeof(mixed) / sizeof(mixed[0]);

    qsort(mixed, size, sizeof(Mixed), compareMixed);

    for (int i = 0; i < size; i++) {
        if (mixed[i].type == INT) {
            printf("%d ", mixed[i].asInt);
        } else {
            printf("%s ", mixed[i].asString);
        }
    }

    freeMixed(mixed, size);

    return 0;
}