#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat_adjacent(char *tuple1, char *tuple2) {
    size_t len1 = strlen(tuple1);
    size_t len2 = strlen(tuple2);
    char *result = (char *)malloc(len1 + len2 + 1);
    if (result == NULL) {
        return NULL;
    }
    memcpy(result, tuple1, len1);
    memcpy(result + len1, tuple2, len2 + 1);
    return result;
}

void free_tuple(char **tuple) {
    if (*tuple != NULL) {
        free(*tuple);
        *tuple = NULL;
    }
}

int main() {
    char *tuple1 = "hello";
    char *tuple2 = " world";
    char *result = concat_adjacent(tuple1, tuple2);
    if (result != NULL) {
        printf("%s\n", result);
        free_tuple(&result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}