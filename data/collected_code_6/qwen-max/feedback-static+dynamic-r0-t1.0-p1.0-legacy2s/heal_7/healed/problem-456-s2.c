#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverse_string(const char* str) {
    int len = strlen(str);
    char* reversed = (char*)malloc((len + 1) * sizeof(char));
    if (reversed == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; ++i) {
        reversed[len - i - 1] = str[i];
    }
    reversed[len] = '\0';
    return reversed;
}

void free_strings(char** strings, int count) {
    for (int i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    const char* input_strings[] = {"deR", "neerG", "eulB", "etihW", "kcalB"};
    int num_strings = 5;
    char** reversed_strings = (char**)malloc(num_strings * sizeof(char*));
    if (reversed_strings == NULL) {
        return 1;
    }
    for (int i = 0; i < num_strings; ++i) {
        reversed_strings[i] = reverse_string(input_strings[i]);
        if (reversed_strings[i] == NULL) {
            free_strings(reversed_strings, i);
            return 1;
        }
    }
    for (int i = 0; i < num_strings; ++i) {
        printf("%s\n", reversed_strings[i]);
    }
    free_strings(reversed_strings, num_strings);
    return 0;
}