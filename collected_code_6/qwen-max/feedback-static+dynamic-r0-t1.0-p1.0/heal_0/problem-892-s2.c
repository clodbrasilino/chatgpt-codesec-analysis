#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *compress_spaces(const char *input) {
    int input_len = strlen(input);
    char *output = (char *)malloc(input_len + 1);
    if (!output) return NULL;

    int output_index = 0;
    int last_space = 0;
    for (int i = 0; i < input_len; ++i) {
        if (input[i] == ' ') {
            if (!last_space) {
                output[output_index++] = ' ';
                last_space = 1;
            }
        } else {
            output[output_index++] = input[i];
            last_space = 0;
        }
    }
    output[output_index] = '\0';

    return output;
}

int main() {
    const char *input = "This   is  a   test  string with  multiple   spaces.  ";
    char *output = compress_spaces(input);

    if (output) {
        printf("Compressed: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}