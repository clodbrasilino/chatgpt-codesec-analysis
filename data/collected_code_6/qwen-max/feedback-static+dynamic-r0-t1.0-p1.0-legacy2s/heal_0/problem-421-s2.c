#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* join_tuple(const char **tuple, int size, const char *delimiter) {
    if (size <= 0 || !tuple || !delimiter) return NULL;

    int total_len = 0;
    for (int i = 0; i < size; ++i) {
        if (tuple[i]) total_len += strlen(tuple[i]);
    }
    int delimiter_len = strlen(delimiter);
    int result_len = total_len + delimiter_len * (size - 1) + 1;

    char *result = (char *)malloc(result_len * sizeof(char));
    if (!result) return NULL;

    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        if (i > 0) strcat(result, delimiter);
        if (tuple[i]) strcat(result, tuple[i]);
    }

    return result;
}

int main() {
    const char *tuple[] = {"one", "two", "three"};
    const char *delimiter = "-";

    char *result = join_tuple(tuple, 3, delimiter);
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}