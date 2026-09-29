#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_with_colon(const char* str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

    if (len == 0) {
        char* empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t bufsize = len * 2 + 1;
    char* result = malloc(bufsize);
    if (result == NULL) {
        return NULL;
    }

    const char* p = str;
    const char* end = str + len;
    size_t offset = 0;

    while (p < end) {
        if (offset + 1 >= bufsize) {
            bufsize *= 2;
            char* new_result = realloc(result, bufsize);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }
            result = new_result;
        }
        if (*p == ' ' || *p == ',' || *p == '.') {
            result[offset++] = ':';
        } else {
            result[offset++] = *p;
        }
        p++;
    }

    if (offset + 1 >= bufsize) {
        bufsize = offset + 1;
        char* new_result = realloc(result, bufsize);
        if (new_result == NULL) {
            free(result);
            return NULL;
        }
        result = new_result;
    }
    result[offset] = '\0';

    char* final_result = realloc(result, offset + 1);
    if (final_result != NULL) {
        result = final_result;
    }

    return result;
}

int main(int argc, char* argv[]) {
    const char* input = "Hello world, this.is a test";
    size_t len = strnlen(input, 1024);
    
    char* output = replace_with_colon(input, len);
    if (output == NULL) {
        fprintf(stderr, "Replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    return EXIT_SUCCESS;
}