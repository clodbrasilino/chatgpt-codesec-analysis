#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void extract_rear(char *output[], const char *input[], int len) {
    for (int i = 0; i < len; ++i) {
        if (input[i] == NULL || input[i][0] == '\0') {
            output[i] = (char *)malloc(1);
            if (output[i]) {
                output[i][0] = '\0';
            }
            continue;
        }
        size_t str_len = strlen(input[i]);
        output[i] = (char *)malloc(2);
        if (output[i]) {
            output[i][0] = input[i][str_len - 1];
            output[i][1] = '\0';
        }
    }
}

int main() {
    const char *strings[] = {"hello", "world", "", NULL};
    int len = sizeof(strings) / sizeof(strings[0]);
    char *results[len];

    extract_rear(results, strings, len);

    for (int i = 0; i < len; ++i) {
        if (results[i] != NULL) {
            printf("%s\n", results[i]);
            free(results[i]);
        }
    }

    return 0;
}