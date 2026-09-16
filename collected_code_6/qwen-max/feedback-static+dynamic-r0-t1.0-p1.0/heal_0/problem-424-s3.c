#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extract_rear_index_elements(char *output[], char **input, int n) {
    for (int i = 0; i < n; ++i) {
        if (input[i] != NULL && input[i][0] != '\0') {
            int length = strlen(input[i]);
            output[i] = (char *)malloc((length + 1) * sizeof(char));
            if (output[i] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            output[i][0] = input[i][length - 1];
            output[i][1] = '\0';
        } else {
            output[i] = (char *)malloc(1 * sizeof(char));
            if (output[i] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            output[i][0] = '\0';
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "!", "", NULL};
    int n = 5;
    char *result[n];

    extract_rear_index_elements(result, strings, n);

    for (int i = 0; i < n; ++i) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    return 0;
}