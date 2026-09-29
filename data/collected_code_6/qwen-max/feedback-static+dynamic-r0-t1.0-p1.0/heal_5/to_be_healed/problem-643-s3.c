#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool contains_z_not_at_edges(const char *word, size_t len) {
    for (size_t i = 1; i < len - 1; ++i) {
        if (word[i] == 'z') {
            return true;
        }
    }
    return false;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[80];
    printf("Enter a word: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%79s", word) != 1) {
        return 1;
    }

    size_t len = strnlen(word, 80);
    if (len > 0 && contains_z_not_at_edges(word, len)) {
        printf("The word contains 'z' not at the start or end.\n");
    } else {
        printf("The word does not contain 'z' not at the start or end.\n");
    }

    return 0;
}