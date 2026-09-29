#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[100];
} Tuple;

Tuple* extract_singles(Tuple* tuples, int n) {
    Tuple* result = (Tuple*)malloc(n * sizeof(Tuple));
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
            result[count++] = tuples[i];
        }
    }
    Tuple* temp = (Tuple*)realloc(result, count * sizeof(Tuple));
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
        for (int i = 0; i < n - 1; ++i) {
            printf("%d: %s\n", singles[i].key, singles[i].value);
        }
        free(singles);
    }
    return 0;
}