#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_z_not_ends(const char *word)
{
    size_t len;
    size_t i;

    if (word == NULL) {
        return false;
    }

    len = strlen(word);
    if (len < 3U) {
        return false;
    }

    for (i = 1U; i < len - 1U; i++) {
        if (word[i] == 'z') {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (match_z_not_ends(buffer)) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
    }

    return 0;
}