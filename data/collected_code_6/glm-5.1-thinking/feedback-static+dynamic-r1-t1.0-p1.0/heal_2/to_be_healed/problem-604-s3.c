#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_range(char *start, char *end) {
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

char *reverse_words(const char *str) {
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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, str, len + 1);

    if (len == 0) {
        return result;
    }

    reverse_range(result, result + len - 1);

    char *word_start = result;
    char *p = result;

    while (*p) {
        if (*p == ' ') {
            reverse_range(word_start, p - 1);
            word_start = p + 1;
        }
        p++;
    }
    reverse_range(word_start, p - 1);

    return result;
}

int main(void) {
    const char *input1 = "Hello world from C";
    char *output1 = reverse_words(input1);
    if (output1 != NULL) {
        printf("Input: \"%s\"\n", input1);
        printf("Output: \"%s\"\n", output1);
        free(output1);
    }

    const char *input2 = "";
    char *output2 = reverse_words(input2);
    if (output2 != NULL) {
        printf("Input: \"%s\"\n", input2);
        printf("Output: \"%s\"\n", output2);
        free(output2);
    }

    /* Possible weaknesses found:
     *  Variable 'output3' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'output3' during its initialization is never read [deadcode.DeadStores]
     */
    const char *output3 = reverse_words(NULL);
    printf("NULL input handled successfully.\n");

    return 0;
}