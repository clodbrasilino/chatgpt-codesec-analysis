#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* replace_char(char* str, char old_char, char new_char) {
    if (str == NULL) {
        return NULL;
    }

    char* current = str;
    while (*current != '\0') {
        if (*current == old_char) {
            *current = new_char;
        }
        current++;
    }
    return str;
}

int main(void) {
    char* buffer = NULL;
    size_t buffer_size = 0;
    ssize_t input_length;
    char old_char, new_char;

    printf("Enter a string: ");
    input_length = getline(&buffer, &buffer_size, stdin);
    if (input_length == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (input_length > 0 && buffer[input_length - 1] == '\n') {
        buffer[input_length - 1] = '\0';
        input_length--;
    }

    if (input_length >= 128) {
        fprintf(stderr, "Error: Input string too long\n");
        free(buffer);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char safe_buffer[128];
    memset(safe_buffer, 0, sizeof(safe_buffer));
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(safe_buffer, buffer, sizeof(safe_buffer) - 1);
    safe_buffer[sizeof(safe_buffer) - 1] = '\0';
    free(buffer);
    buffer = NULL;

    printf("Enter character to replace: ");
    if (scanf(" %c", &old_char) != 1) {
        fprintf(stderr, "Error reading old character\n");
        return 1;
    }

    printf("Enter replacement character: ");
    if (scanf(" %c", &new_char) != 1) {
        fprintf(stderr, "Error reading new character\n");
        return 1;
    }

    char* result = replace_char(safe_buffer, old_char, new_char);
    if (result == NULL) {
        fprintf(stderr, "Error: NULL string\n");
        return 1;
    }

    printf("Result: %s\n", result);

    return 0;
}