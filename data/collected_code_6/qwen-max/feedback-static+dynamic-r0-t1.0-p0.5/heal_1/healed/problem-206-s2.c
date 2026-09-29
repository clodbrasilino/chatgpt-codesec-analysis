#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char *a, const char *b) {
    size_t len_a = strnlen(a, 1024);
    size_t len_b = strnlen(b, 1024);
    char *result = (char *)malloc(len_a + len_b + 1);
    if (result == NULL) {
        return NULL;
    }
    snprintf(result, len_a + len_b + 1, "%s%s", a, b);
    return result;
}

void process_tuples(const char *tuples[], int count) {
    for (int i = 0; i < count - 1; i++) {
        char *concatenated = concatenate(tuples[i], tuples[i + 1]);
        if (concatenated != NULL) {
            printf("%s\n", concatenated);
            free(concatenated);
        }
    }
}

int main() {
    const char *tuples[] = {"hello", "world", "this", "is", "a", "test"};
    int count = sizeof(tuples) / sizeof(tuples[0]);
    process_tuples(tuples, count);
    return 0;
}