#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split_string_to_chars(const char *input, char ***output, int *len) {
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'len==NULL' is redundant or there is possible null pointer dereference: len. [nullPointerRedundantCheck]
     */
    *len = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'len==NULL' is not redundant
     */
    if (input == NULL || output == NULL || len == NULL) return;

    *len = strlen(input);
    *output = (char **)malloc(*len * sizeof(char *));
    if (*output == NULL) return;

    for (int i = 0; i < *len; ++i) {
        (*output)[i] = (char *)malloc(2 * sizeof(char));
        if ((*output)[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free((*output)[j]);
            }
            free(*output);
            *output = NULL;
            *len = 0;
            return;
        }
        (*output)[i][0] = input[i];
        (*output)[i][1] = '\0';
    }
}

int main() {
    const char *str = "Hello, World!";
    char **result;
    int length;

    split_string_to_chars(str, &result, &length);

    for (int i = 0; i < length; ++i) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}