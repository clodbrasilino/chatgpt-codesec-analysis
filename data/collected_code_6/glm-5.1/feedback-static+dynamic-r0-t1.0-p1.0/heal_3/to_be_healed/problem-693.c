#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  */

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;

    while (src_pos < len) {
        if (str[src_pos] == ' ') {
            result[dst_pos++] = ' ';
            while (src_pos < len && str[src_pos] == ' ') {
                src_pos++;
            }
        } else {
            result[dst_pos++] = str[src_pos++];
        }
    }

    result[dst_pos] = '\0';

    return result;
}

int main(void) {
    const char *input0 = "Google  Assistant";
    char *output0 = remove_multiple_spaces(input0);
    if (output0 != NULL) {
        printf("%s\n", output0);
        free(output0);
    }

    const char *input1 = "Quad    Core";
    char *output1 = remove_multiple_spaces(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "ChromeCast   Built-in";
    char *output2 = remove_multiple_spaces(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    return 0;
}