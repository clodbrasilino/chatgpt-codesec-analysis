#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t input_len, output_size, output_index = 0;
    char *output = NULL;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, 8192);
    output_size = input_len + 1;

    output = (char *)malloc(output_size);
    if (output == NULL) {
        return NULL;
    }

    int ret = regcomp(&regex, "[[:alnum:]]", REG_EXTENDED);
    if (ret != 0) {
        output[0] = '\0';
        return output;
    }

    cursor = input;
    while (*cursor != '\0' && regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so == -1) {
            break;
        }
        if (output_index < input_len) {
            output[output_index++] = cursor[match.rm_so];
        } else {
            break;
        }
        cursor += match.rm_so + 1;
    }

    if (output_index < output_size) {
        output[output_index] = '\0';
    } else {
        output[output_size - 1] = '\0';
    }
    regfree(&regex);
    return output;
}

int main(void) {
    const char *input = "Hello, World! 123 ...";
    char *output = remove_non_alphanumeric(input);

    if (output != NULL) {
        printf("Input: %s\n", input);
        printf("Output: %s\n", output);
        free(output);
    } else {
        printf("Error processing input\n");
    }

    return 0;
}