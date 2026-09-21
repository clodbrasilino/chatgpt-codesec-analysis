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
        size_t len = strcspn(buffer, "\n");
        buffer[len] = '\0';

        if (contains_z_not_at_edges(buffer, len)) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
    }

    return 0;
}