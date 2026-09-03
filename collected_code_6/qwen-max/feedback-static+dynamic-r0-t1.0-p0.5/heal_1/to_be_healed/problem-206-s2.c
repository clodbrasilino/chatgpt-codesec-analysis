#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    char *result = (char *)malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, a);
    strcat(result, b);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as const array [constParameter]
 */
void process_tuples(char *tuples[], int count) {
    for (int i = 0; i < count - 1; i++) {
        char *concatenated = concatenate(tuples[i], tuples[i + 1]);
        if (concatenated != NULL) {
            printf("%s\n", concatenated);
            free(concatenated);
        }
    }
}

int main() {
    char *tuples[] = {"hello", "world", "this", "is", "a", "test"};
    int count = sizeof(tuples) / sizeof(tuples[0]);
    process_tuples(tuples, count);
    return 0;
}