#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_multiple_spaces(char **str) {
    if (str == NULL || *str == NULL) {
        return -1;
    }

    char *read_ptr = *str;
    char *write_ptr = *str;
    int in_space = 0;

    while (*read_ptr != '\0') {
        if (*read_ptr == ' ') {
            if (!in_space) {
                *write_ptr++ = *read_ptr;
                in_space = 1;
            }
        } else {
            *write_ptr++ = *read_ptr;
            in_space = 0;
        }
        read_ptr++;
    }
    *write_ptr = '\0';

    size_t new_len = (size_t)(write_ptr - *str);
    char *resized = realloc(*str, new_len + 1);
    if (resized != NULL) {
        *str = resized;
    }

    return 0;
}

int main(void) {
    const char *initial_text = "This   is  a    test string   with multiple     spaces.";
    
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (initial_text[len] != '\0' && len < 4096) {
        len++;
    }

    char *text = malloc(len + 1);
    if (text == NULL) {
        return 1;
    }

    snprintf(text, len + 1, "%s", initial_text);

    printf("Original: '%s'\n", text);

    if (remove_multiple_spaces(&text) == 0) {
        printf("Modified: '%s'\n", text);
    } else {
        printf("Error processing string.\n");
    }

    free(text);
    return 0;
}