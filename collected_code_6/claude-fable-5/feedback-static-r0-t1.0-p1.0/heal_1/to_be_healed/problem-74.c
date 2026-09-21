#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool follows_pattern(const char *pattern, const char *text)
{
    bool result = true;
    size_t plen;
    size_t i = 0;
    size_t j;
    char *copy = NULL;
    char *token = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *map[256] = { NULL };

    if (pattern == NULL || text == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    plen = strlen(pattern);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    copy = malloc(strlen(text) + 1U);
    if (copy == NULL) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(copy, text);

    token = strtok(copy, " ");
    while (token != NULL) {
        if (i >= plen) {
            result = false;
            break;
        }
        unsigned char c = (unsigned char)pattern[i];
        if (map[c] != NULL) {
            if (strcmp(map[c], token) != 0) {
                result = false;
                break;
            }
        } else {
            for (j = 0U; j < 256U; j++) {
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
        token = strtok(NULL, " ");
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
                   patterns[i], texts[i], ok ? "matches" : "does not match") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}