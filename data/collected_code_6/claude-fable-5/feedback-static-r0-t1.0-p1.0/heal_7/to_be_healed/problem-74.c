#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 4096U
#define MAP_SIZE 256U

static bool follows_pattern(const char *pattern, const char *text)
{
    bool result = true;
    size_t plen;
    size_t tlen;
    size_t i = 0U;
    size_t j;
    char *copy = NULL;
    char *token = NULL;
    char *saveptr = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *map[MAP_SIZE] = { NULL };

    if (pattern == NULL || text == NULL) {
        return false;
    }

    plen = strnlen(pattern, MAX_INPUT_LEN);
    tlen = strnlen(text, MAX_INPUT_LEN);

    if (plen >= MAX_INPUT_LEN || tlen >= MAX_INPUT_LEN) {
        return false;
    }

    copy = calloc(tlen + 1U, sizeof(char));
    if (copy == NULL) {
        return false;
    }

    if (tlen > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, text, tlen);
    }
    copy[tlen] = '\0';

    token = strtok_r(copy, " ", &saveptr);
    while (token != NULL) {
        if (i >= plen) {
            result = false;
            break;
        }

        unsigned char c = (unsigned char)pattern[i];
        if ((size_t)c >= MAP_SIZE) {
            result = false;
            break;
        }

        if (map[c] != NULL) {
            if (strcmp(map[c], token) != 0) {
                result = false;
                break;
            }
        } else {
            for (j = 0U; j < MAP_SIZE; j++) {
                if ((map[j] != NULL) && (strcmp(map[j], token) == 0)) {
                    result = false;
                    break;
                }
            }
            if (!result) {
                break;
            }
            map[c] = token;
        }

        i++;
        token = strtok_r(NULL, " ", &saveptr);
    }

    if (result && (i != plen)) {
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
    size_t i;

    for (i = 0U; i < count; i++) {
        bool ok = follows_pattern(patterns[i], texts[i]);
        if (printf("Pattern \"%s\" with \"%s\": %s\n",
                   patterns[i], texts[i],
                   ok ? "matches" : "does not match") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}