#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int validate_string(const char *input) {
    regex_t regex;
    int ret;
    int result = 0;

    if (input == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }

    ret = regexec(&regex, input, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret != REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;
    int validation_result;

    printf("Enter a string to validate: ");

    line_length = getline(&buffer, &buffer_size, stdin);

    if (line_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (line_length > 0 && buffer[line_length - 1] == '\n') {
        buffer[line_length - 1] = '\0';
        line_length--;
    }

    validation_result = validate_string(buffer);

    free(buffer);

    if (validation_result) {
        printf("Valid: String contains only alphanumeric characters\n");
        return EXIT_SUCCESS;
    } else {
        printf("Invalid: String contains invalid characters or is empty\n");
        return EXIT_FAILURE;
    }
}