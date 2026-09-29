#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    char value[100];
} Tuple;

Tuple* extract_singles(Tuple* tuples, int n) {
    Tuple* result = malloc(n * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }
    int count = 0;
    for (int i = 0; i < n; ++i) {
        int is_unique = 1;
        for (int j = 0; j < n; ++j) {
            if (i != j && tuples[i].key == tuples[j].key) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            size_t len = strnlen(tuples[i].value, sizeof(tuples[i].value));
            if (len > 0 && len < sizeof(tuples[i].value)) {
                memcpy(result[count].value, tuples[i].value, len);
                result[count].value[len] = '\0';
                result[count].key = tuples[i].key;
                count++;
            }
        }
    }
    Tuple* temp = realloc(result, count * sizeof(Tuple));
    if (temp == NULL) {
        free(result);
        return NULL;
    }
    result = temp;
    return result;
}

int main() {
    Tuple tuples[] = {{1, "apple"}, {2, "banana"}, {1, "cherry"}, {3, "date"}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    Tuple* singles = extract_singles(tuples, n);
    if (singles) {
        int count = 0;
        while (count < n && singles[count].key != 0) {
            printf("%d: %s\n", singles[count].key, singles[count].value);
            count++;
        }
        free(singles);
    }
    return 0;
}