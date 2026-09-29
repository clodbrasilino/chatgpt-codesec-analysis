/* Possible weaknesses found:
 *  glib.h: No such file or directory
 *  'glib.h' file not found
 */
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_duplicate_words(const char *input)
{
    GHashTable *seen;
    GString *result;
    gchar **words;
    gchar *output;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    words = g_strsplit_set(input, " \t\r\n\v\f", -1);
    if (words == NULL) {
        return NULL;
    }

    seen = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    if (seen == NULL) {
        g_strfreev(words);
        return NULL;
    }

    result = g_string_new(NULL);
    if (result == NULL) {
        g_hash_table_destroy(seen);
        g_strfreev(words);
        return NULL;
    }

    for (i = 0; words[i] != NULL; ++i) {
        gchar *word;

        if (words[i][0] == '\0' ||
            g_hash_table_contains(seen, words[i])) {
            continue;
        }

        word = g_strdup(words[i]);
        if (word == NULL) {
            g_string_free(result, TRUE);
            g_hash_table_destroy(seen);
            g_strfreev(words);
            return NULL;
        }

        g_hash_table_add(seen, word);

        if (result->len != 0) {
            g_string_append_c(result, ' ');
        }

        g_string_append(result, words[i]);
    }

    output = g_string_free(result, FALSE);
    g_hash_table_destroy(seen);
    g_strfreev(words);

    return output;
}

int main(int argc, char *argv[])
{
    GString *input;
    char *result;
    int i;
    int status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = g_string_new(argv[1]);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 2; i < argc; ++i) {
        g_string_append_c(input, ' ');
        g_string_append(input, argv[i]);
    }

    result = remove_duplicate_words(input->str);
    g_string_free(input, TRUE);

    if (result == NULL) {
        fprintf(stderr, "Failed to process the input string\n");
        return EXIT_FAILURE;
    }

    status = EXIT_SUCCESS;

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    g_free(result);
    return status;
}