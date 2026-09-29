#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str) {
    char result[100] = "";
    int i, j = 0;
    for (i = 0; str[i] != '\0' && j < sizeof(result) - 2; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    strncpy(str, result, sizeof(input) - 1);
    str[sizeof(input) - 1] = '\0';
}

int main() {
    char input[100];
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        remove_odd_index_chars(input);
        printf("Modified string: %s\n", input);
    } else {
        printf("Failed to read input.\n");
    }
    return 0;
}