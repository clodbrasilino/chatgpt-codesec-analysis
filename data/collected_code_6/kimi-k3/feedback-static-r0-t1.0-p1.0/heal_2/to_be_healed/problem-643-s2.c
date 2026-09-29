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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        len = 0;
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