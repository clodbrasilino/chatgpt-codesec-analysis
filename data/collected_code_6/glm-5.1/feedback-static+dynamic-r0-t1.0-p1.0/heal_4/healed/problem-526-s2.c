#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *capitalize_first_last(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    memcpy(result, str, len + 1);

    size_t i = 0;
    while (i < len) {
        while (i < len && isspace((unsigned char)result[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        size_t start = i;
        while (i < len && !isspace((unsigned char)result[i])) {
            i++;
        }
        size_t end = i - 1;

        result[start] = (char)toupper((unsigned char)result[start]);
        if (end != start) {
            result[end] = (char)toupper((unsigned char)result[end]);
        }
    }

    result[len] = '\0';
    return result;
}

int main(void) {
    const char *input1 = "Python";
    const char *input2 = "BigdatA";
    const char *input3 = "HadooP";
    const char *input4 = "hello world from c programming";
    
    char *output;

    output = capitalize_first_last(input1);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    output = capitalize_first_last(input2);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    output = capitalize_first_last(input3);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    output = capitalize_first_last(input4);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}