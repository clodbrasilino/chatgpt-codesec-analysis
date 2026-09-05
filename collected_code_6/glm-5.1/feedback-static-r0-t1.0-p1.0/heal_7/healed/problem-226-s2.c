#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len / 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklmnopqrstuvwxyz";
    char *output = remove_odd_index_chars(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    const char *null_input = NULL;
    const char *null_output = remove_odd_index_chars(null_input);
    
    if (null_output == NULL) {
        printf("NULL input handled correctly.\n");
    }

    return 0;
}