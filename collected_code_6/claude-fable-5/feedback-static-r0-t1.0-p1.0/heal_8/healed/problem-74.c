#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_LEN 4096U
#define MAP_SIZE ((size_t)UCHAR_MAX + 1U)

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
    const char **map = NULL;

    if (pattern == NULL || text == NULL) {
        return false;
    }

    plen = strnlen(pattern, MAX_INPUT_LEN);
    tlen = strnlen(text, MAX_INPUT_LEN);

    if (plen >= MAX_INPUT_LEN || tlen >= MAX_INPUT_LEN) {
        return false;
    }

    map = calloc(MAP_SIZE, sizeof(*map));
    if (map == NULL) {
        return false;
    }

    copy = strndup(text, tlen);
    if (copy == NULL) {
        free(map);
        return false;
    }

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
    free(map);
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