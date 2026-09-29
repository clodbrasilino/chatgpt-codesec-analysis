#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LEN 4096U
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
    const char *map[MAP_SIZE];

    if (pattern == NULL || text == NULL) {
        return false;
    }

    for (j = 0U; j < MAP_SIZE; j++) {
        map[j] = NULL;
    }

    plen = strnlen(pattern, MAX_LEN);
    tlen = strnlen(text, MAX_LEN);

    if (plen == 0U || tlen == 0U || plen >= MAX_LEN || tlen >= MAX_LEN) {
        return false;
    }

    if (tlen >= (SIZE_MAX - 1U)) {
        return false;
    }

    copy = malloc(tlen + 1U);
    if (copy == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, text, tlen);
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