#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str, size_t len) {
    char result[len + 1];
    int i, j = 0;
    for (i = 0; i < len && j < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    strncpy(str, result, len);
    str[len] = '\0';
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        remove_odd_index_chars(input, sizeof(input) - 1);
        printf("Modified string: %s\n", input);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}