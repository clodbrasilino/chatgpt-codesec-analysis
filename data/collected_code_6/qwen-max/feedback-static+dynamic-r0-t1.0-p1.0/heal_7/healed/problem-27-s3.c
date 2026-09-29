#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_digits(const char *input) {
    size_t len = 0;
    while (input[len] != '\0') len++;
    char *output = (char *)malloc((len + 1) * sizeof(char));
    if (output == NULL) {
        return NULL;
    }
    int j = 0;
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

void free_strings(char **strings, int n) {
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char *strings[] = {"abc123", "456def789", "ghi0jkl", "mno"};
    int n = sizeof(strings) / sizeof(strings[0]);

    char **new_strings = (char **)malloc(n * sizeof(char *));
    if (new_strings == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        new_strings[i] = remove_digits(strings[i]);
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