#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 4096U
#define ALPHABET_SIZE 26U

static bool follows_pattern(const char *pattern, const char *text)
{
    if (pattern == NULL || text == NULL) {
        return false;
    }

    size_t plen = strnlen(pattern, MAX_INPUT_LEN + 1U);
    if ((plen == 0U) || (plen > MAX_INPUT_LEN)) {
        return false;
    }

    size_t tlen = strnlen(text, MAX_INPUT_LEN + 1U);
    if (tlen > MAX_INPUT_LEN) {
        return false;
    }

    char *copy = calloc(tlen + 1U, sizeof(char));
    if (copy == NULL) {
        return false;
    }
    memcpy(copy, text, tlen);

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