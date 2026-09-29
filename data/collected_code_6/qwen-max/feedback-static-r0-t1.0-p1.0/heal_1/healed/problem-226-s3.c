#include <stdio.h>
#include <string.h>

void remove_odd_index_chars(char *str) {
    int i, j = 0;
    char temp[100];
    for (i = 0; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            temp[j++] = str[i];
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
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