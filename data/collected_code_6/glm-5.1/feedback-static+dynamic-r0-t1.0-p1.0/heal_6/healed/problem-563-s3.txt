#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_quoted(const char *input) {
    const char *start;
    const char *end;
    size_t length;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    start = strchr(input, '"');
    if (start == NULL) {
        return NULL;
    }

    start++;

    end = strchr(start, '"');
    if (end == NULL) {
        return NULL;
    }

    length = (size_t)(end - start);
    result = (char *)malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, start, length);
    result[length] = '\0';

    return result;
}

int main(void) {
    const char *text = "This is a \"test string\" for extraction.";
    char *extracted = extract_quoted(text);

    if (extracted != NULL) {
        printf("%s\n", extracted);
        free(extracted);
    } else {
        printf("No quoted value found.\n");
    }

    return 0;
}