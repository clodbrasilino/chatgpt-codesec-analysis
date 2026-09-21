#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *str, size_t buf_size) {
    if (str == NULL || buf_size == 0) {
        return;
    }
    size_t len = strnlen(str, buf_size);
    if (len < 2) {
        return;
    }
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main(void) {
    char *buffer = calloc(256, sizeof(char));
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }
    if (fgets(buffer, 256, stdin) == NULL) {
        free(buffer);
        return EXIT_FAILURE;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    sort_string(buffer, 256);
    printf("%s\n", buffer);
    free(buffer);
    return EXIT_SUCCESS;
}