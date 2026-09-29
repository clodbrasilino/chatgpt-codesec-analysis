#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PATTERN_LEN 1024U
#define MAX_TEXT_LEN 65536U
#define ALPHABET_SIZE 26U

static bool follows_pattern(const char *pattern, const char *text)
{
    if (pattern == NULL || text == NULL) {
        return false;
    }

    size_t plen = strnlen(pattern, MAX_PATTERN_LEN + 1U);
    if (plen == 0U || plen > MAX_PATTERN_LEN) {
        return false;
    }

    size_t tlen = strnlen(text, MAX_TEXT_LEN + 1U);
    if (tlen > MAX_TEXT_LEN) {
        return false;
    }

    /* Possible weaknesses found:
     *  copy_size is assigned 'tlen+1U' here.
     */
    size_t copy_size = tlen + 1U;
    char *copy = malloc(copy_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     *  Condition 'tlen<copy_size' is always true [knownConditionTrueFalse]
     *  Condition 'tlen<copy_size' is always true
     */
    if (tlen > 0U && tlen < copy_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, text, tlen);
    }
    copy[tlen] = '\0';

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *map[ALPHABET_SIZE] = { NULL };
    bool result = true;
    size_t i = 0U;
    char *saveptr = NULL;

    char *word = strtok_r(copy, " ", &saveptr);
    while ((word != NULL) && (i < plen)) {
        char c = pattern[i];
        if ((c < 'a') || (c > 'z')) {
            result = false;
            break;
        }
        size_t idx = (size_t)(c - 'a');
        if (idx >= ALPHABET_SIZE) {
            result = false;
            break;
        }
        if (map[idx] == NULL) {
            for (size_t j = 0U; j < ALPHABET_SIZE; j++) {
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
        word = strtok_r(NULL, " ", &saveptr);
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