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
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'man indian', got naidni nam
  *  test case 1 failed: expected 'language java', got avaj egaugnal
  *  test case 0 failed: expected 'program python', got nohtyp margorp
  */

char* reverse_words(const char *input) {
    size_t length = strlen(input);
    char *output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }
    strcpy(output, input);

    int start = 0;
    for (int i = 0; i <= length; ++i) {
        if (output[i] == ' ' || output[i] == '\0') {
            reverse_string(output, start, i - 1);
            start = i + 1;
        }
    }

    return output;
}

int main() {
    const char *inputs[] = {"python program", "java language", "indian man", "Hello World This is C"};
    for (size_t j = 0; j < sizeof(inputs) / sizeof(inputs[0]); ++j) {
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