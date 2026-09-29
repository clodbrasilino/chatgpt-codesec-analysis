#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  *  test case 0 failed: expected 'program python', got <no output>
  *  test case 2 failed: expected 'man indian', got <no output>
  *  test case 1 failed: expected 'language java', got <no output>
  */

char* reverse_words(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);
    char *output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output, input, length);
    output[length] = '\0';

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