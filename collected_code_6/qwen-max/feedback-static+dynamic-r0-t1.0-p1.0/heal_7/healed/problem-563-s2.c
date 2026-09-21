#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *extract_quoted(const char *input) {
    if (input == NULL || input[0] == '\0') return NULL;

    size_t length = strlen(input);
    int in_quote = 0;
    int index = 0;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == '\"') {
            in_quote = !in_quote;
            continue;
        }

        if (in_quote) {
            ++index;
        }
    }

    if (index == 0) return NULL;

    char *buffer = (char *)malloc(index + 1);
    if (buffer == NULL) return NULL;

    in_quote = 0;
    index = 0;

    for (size_t i = 0; i < length; ++i) {
        if (input[i] == '\"') {
            in_quote = !in_quote;
            continue;
        }

        if (in_quote) {
            buffer[index++] = input[i];
        }
    }

    buffer[index] = '\0';
    return buffer;
}

int main() {
    const char *test_string = "This is a \"sample\" test with multiple \"values\" quoted.";
    char *extracted = extract_quoted(test_string);

    if (extracted != NULL) {
        printf("Extracted: %s\n", extracted);
        free(extracted);
    } else {
        printf("No values found or allocation failed.\n");
    }

    return 0;
}