#include <stdio.h>
#include <string.h>
#include <ctype.h>

int contains_z_not_at_edges(const char *word) {
    size_t len;
    size_t i;

    if (word == NULL) {
        return 0;
    }

    len = strlen(word);
    if (len < 3) {
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
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (contains_z_not_at_edges(buffer)) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
    }

    return 0;
}