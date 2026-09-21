#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *my_strdup(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s) + 1;
    char *new_s = malloc(len);
    if (new_s == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    return memcpy(new_s, s, len);
}

static int ci_strcmp(const char *a, const char *b) {
    while (*a && *b) {
        int diff = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (diff != 0) return diff;
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *find_first_repeated_word(const char *str) {
    if (str == NULL) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *temp = malloc(len + 1);
    if (temp == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp, str);

    size_t capacity = 16;
    size_t count = 0;
    char **seen = malloc(capacity * sizeof(char *));
    if (seen == NULL) {
        free(temp);
        return NULL;
    }

    const char *delim = " ,.!?;:\t\n\r";
    char *token = strtok(temp, delim);
    char *result = NULL;

    while (token != NULL) {
        for (size_t i = 0; i < count; i++) {
            if (ci_strcmp(seen[i], token) == 0) {
                result = my_strdup(token);
                free(temp);
                for (size_t j = 0; j < count; j++) free(seen[j]);
                free(seen);
                return result;
            }
        }

        if (count >= capacity) {
            capacity *= 2;
            char **new_seen = realloc(seen, capacity * sizeof(char *));
            if (new_seen == NULL) {
                free(temp);
                for (size_t j = 0; j < count; j++) free(seen[j]);
                free(seen);
                return NULL;
            }
            seen = new_seen;
        }

        seen[count] = my_strdup(token);
        if (seen[count] == NULL) {
            free(temp);
            for (size_t j = 0; j < count; j++) free(seen[j]);
            free(seen);
            return NULL;
        }
        count++;

        token = strtok(NULL, delim);
    }

    free(temp);
    for (size_t j = 0; j < count; j++) free(seen[j]);
    free(seen);
    return NULL;
}

int main(void) {
    const char *text = "This is a test, this is only a test.";
    char *repeated = find_first_repeated_word(text);
    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No repeated word found.\n");
    }
    return 0;
}