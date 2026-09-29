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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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