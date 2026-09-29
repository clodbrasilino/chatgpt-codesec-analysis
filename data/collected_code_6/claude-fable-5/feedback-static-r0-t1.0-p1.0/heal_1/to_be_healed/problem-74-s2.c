#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool follows_pattern(const char *pattern, const char *text)
{
    if (pattern == NULL || text == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t plen = strlen(pattern);
    if (plen == 0U) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t tlen = strlen(text);
    char *copy = malloc(tlen + 1U);
    if (copy == NULL) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, text, tlen + 1U);

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *map[26] = { NULL };
    bool result = true;
    size_t i = 0U;

    char *word = strtok(copy, " ");
    while ((word != NULL) && (i < plen)) {
        char c = pattern[i];
        if ((c < 'a') || (c > 'z')) {
            result = false;
            break;
        }
        int idx = (int)(c - 'a');
        if (map[idx] == NULL) {
            for (int j = 0; j < 26; j++) {
                if ((map[j] != NULL) && (strcmp(map[j], word) == 0)) {
                    result = false;
                    break;
                }
            }
            if (!result) {
                break;
            }
            map[idx] = word;
        } else {
            if (strcmp(map[idx], word) != 0) {
                result = false;
                break;
            }
        }
        i++;
        word = strtok(NULL, " ");
    }

    if (result && ((word != NULL) || (i != plen))) {
        result = false;
    }

    free(copy);
    return result;
}

int main(void)
{
    const char *patterns[] = { "abba", "abba", "aaaa", "abba" };
    const char *texts[] = {
        "dog cat cat dog",
        "dog cat cat fish",
        "dog cat cat dog",
        "dog dog dog dog"
    };
    size_t count = sizeof(patterns) / sizeof(patterns[0]);

    for (size_t i = 0U; i < count; i++) {
        bool ok = follows_pattern(patterns[i], texts[i]);
        int printed = printf("Pattern \"%s\" with \"%s\": %s\n",
                             patterns[i], texts[i], ok ? "true" : "false");
        if (printed < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}