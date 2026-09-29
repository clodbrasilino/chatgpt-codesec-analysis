#include <stdio.h>
#include <string.h>

int contains_z_not_at_edges(const char *word, size_t len) {
    size_t i;

    if (word == NULL || len < 3) {
        return 0;
    }

    for (i = 1; i < len - 1; i++) {
        if (word[i] == 'z') {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = 0;
        size_t i;

        for (i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '\0') {
                break;
            }
            len++;
        }

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        if (contains_z_not_at_edges(buffer, len)) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
    }

    return 0;
}