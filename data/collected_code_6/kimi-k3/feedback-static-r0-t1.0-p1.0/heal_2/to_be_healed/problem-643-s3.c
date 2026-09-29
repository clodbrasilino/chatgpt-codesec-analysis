#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_z_not_ends(const char *word, size_t max_len)
{
    size_t len;
    size_t i;

    if (word == NULL) {
        return false;
    }

    len = strnlen(word, max_len);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (match_z_not_ends(buffer, sizeof(buffer))) {
            printf("Match\n");
        } else {
            printf("No match\n");
        }
    }

    return 0;
}