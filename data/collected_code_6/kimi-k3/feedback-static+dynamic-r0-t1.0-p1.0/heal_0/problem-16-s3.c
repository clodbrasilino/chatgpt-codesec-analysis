#include <stdio.h>
#include <string.h>
#include <ctype.h>

void find_lowercase_underscore_sequences(const char *str) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    size_t i = 0;
    int found = 0;

    while (i < len) {
        if (islower((unsigned char)str[i])) {
            size_t start = i;
            size_t count = 0;

            while (i < len && (islower((unsigned char)str[i]) || str[i] == '_')) {
                if (str[i] == '_') {
                    count++;
                }
                i++;
            }

            if (count > 0 && i > start && str[i - 1] != '_') {
                printf("Found sequence: ");
                for (size_t j = start; j < i; j++) {
                    putchar(str[j]);
                }
                putchar('\n');
                found = 1;
            }
        } else {
            i++;
        }
    }

    if (!found) {
        printf("No sequences found.\n");
    }
}

int main(void) {
    char input[1024];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    find_lowercase_underscore_sequences(input);

    return 0;
}