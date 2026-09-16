#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenate_tuples(const char* tuple1[2], const char* tuple2[2]) {
    char** result = (char**)malloc(4 * sizeof(char*));
    int i;
    for (i = 0; i < 2; ++i) {
        result[i] = strdup(tuple1[i]);
    }
    for (i = 0; i < 2; ++i) {
        result[i + 2] = strdup(tuple2[i]);
    }
    return result;
}

int main() {
    const char* tuple1[2] = {"Hello", "World"};
    const char* tuple2[2] = {"C", "Programming"};
    char** concatenated = concatenate_tuples(tuple1, tuple2);
    
    for (int i = 0; i < 4; ++i) {
        printf("%s ", concatenated[i]);
        free(concatenated[i]);
    }
    free(concatenated);
    return 0;
}