#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_digits(const char *input, size_t input_len) {
    char *output = (char *)malloc((input_len + 1) * sizeof(char));
    if (output == NULL) {
        return NULL;
    }
    size_t j = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (!isdigit((unsigned char)input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

void free_strings(char **strings, int n) {
    for (int i = 0; i < n; i++) {
        if (strings[i] != NULL) {
            free(strings[i]);
        }
    }
    free(strings);
}

int main() {
    char *strings[] = {"abc123", "456def789", "ghi0jkl", "mno"};
    int n = sizeof(strings) / sizeof(strings[0]);

    char **new_strings = (char **)malloc(n * sizeof(char *));
    if (new_strings == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        size_t len = strlen(strings[i]);
        new_strings[i] = remove_digits(strings[i], len);
        if (new_strings[i] == NULL) {
            free_strings(new_strings, i);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s\n", new_strings[i]);
    }

    free_strings(new_strings, n);
    return 0;
}