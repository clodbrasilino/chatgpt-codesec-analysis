#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    size_t count = 0;

    while (str[count] != '\0' && count < BUFFER_SIZE) {
        if (isalpha((unsigned char)str[count])) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        count++;
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main(void) {
    char buffer[BUFFER_SIZE];

    printf("Enter a sentence: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (strlen(buffer) >= BUFFER_SIZE - 1 && buffer[BUFFER_SIZE - 2] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }

    int result = longest_word_length(buffer);
    printf("Longest word length: %d\n", result);

    return EXIT_SUCCESS;
}