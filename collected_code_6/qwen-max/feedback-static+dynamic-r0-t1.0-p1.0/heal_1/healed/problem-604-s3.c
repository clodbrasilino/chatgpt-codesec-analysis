#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* reverse_words(const char *input) {
    size_t length = strlen(input);
    char *output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }
    memcpy(output, input, length + 1);

    int start = 0;
    int i;
    for (i = 0; i <= length; ++i) {
        if (output[i] == ' ' || output[i] == '\0') {
            reverse_string(output, start, i - 1);
            start = i + 1;
        }
    }

    return output;
}

int main() {
    const char *inputs[] = {"program python", "language java", "man indian"};
    for (int j = 0; j < 3; ++j) {
        char *result = reverse_words(inputs[j]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("Memory allocation failed.\n");
        }
    }
    return 0;
}