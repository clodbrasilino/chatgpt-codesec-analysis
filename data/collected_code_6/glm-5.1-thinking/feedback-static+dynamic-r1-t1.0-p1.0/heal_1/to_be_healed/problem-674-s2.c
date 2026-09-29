#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Possible weaknesses found:
 *  'glib.h' file not found
 *  glib.h: No such file or directory
 */
#include <glib.h>

char *remove_duplicate_words(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    char *copy = strdup(str);
    if (copy == NULL) {
        return NULL;
    }

    GHashTable *set = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    if (set == NULL) {
        free(copy);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t capacity = strlen(str) + 2;
    char *result = malloc(capacity);
    if (result == NULL) {
        free(copy);
        g_hash_table_destroy(set);
        return NULL;
    }
    result[0] = '\0';

    char *saveptr = NULL;
    const char *delim = " \t\n";
    char *token = strtok_r(copy, delim, &saveptr);
    
    while (token != NULL) {
        if (g_hash_table_lookup(set, token) == NULL) {
            char *key = strdup(token);
            if (key != NULL) {
                g_hash_table_insert(set, key, GINT_TO_POINTER(1));
                if (result[0] != '\0') {
                    /* Possible weaknesses found:
                     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
                     */
                    strcat(result, " ");
                }
                /* Possible weaknesses found:
                 * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
                 */
                strcat(result, token);
            }
        }
        token = strtok_r(NULL, delim, &saveptr);
    }

    g_hash_table_destroy(set);
    free(copy);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t final_len = strlen(result) + 1;
    char *final_result = malloc(final_len);
    if (final_result != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(final_result, result, final_len);
    }
    free(result);

    return final_result;
}

int main(void) {
    const char *text = "hello world hello this is a test test world";
    char *unique = remove_duplicate_words(text);
    if (unique != NULL) {
        printf("%s\n", unique);
        free(unique);
    }
    return 0;
}