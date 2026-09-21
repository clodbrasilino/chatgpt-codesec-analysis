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
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result[count].value, tuples[i].value, sizeof(tuples[i].value) - 1);
                result[count].value[sizeof(tuples[i].value) - 1] = '\0';
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
        for (int count = 0; count < n && singles[count].key != 0; count++) {
            printf("%d: %s\n", singles[count].key, singles[count].value);
        }
        free(singles);
    }
    return 0;
}