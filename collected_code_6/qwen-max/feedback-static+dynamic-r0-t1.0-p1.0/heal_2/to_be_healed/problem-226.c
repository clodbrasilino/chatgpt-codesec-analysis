#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_odd_indexed_chars(const char *input) {
    size_t len = 0;
    /* Possible weaknesses found:
     *  Redundant condition: If 'input[len] != '\0'', the comparison 'input[len] != 0' is always true. [redundantCondition]
     */
    while (input[len] != '\0' && input[len] != 0) len++;
    char *result = (char *)malloc((len / 2 + 1) * sizeof(char));
    if (result == NULL) return NULL;

    for (size_t i = 0, j = 0; i < len; i += 2, j++) {
        result[j] = input[i];
    }
    result[len / 2] = '\0';
    return result;
}

int main() {
    const char *input = "Hello, World!";
    char *output = remove_odd_indexed_chars(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}