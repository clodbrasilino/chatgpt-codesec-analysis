#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contains_substring(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) {
        return 0;
    }
    return strstr(str, substr) != NULL;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red &","Orange+","Green"]
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red color","Orange#","Green"]
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got ["Red &"]
  */

static char **remove_words(char **words, int word_count, const char *filter, int *result_count) {
    if (words == NULL || filter == NULL || result_count == NULL || word_count <= 0) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    char **result = (char **)malloc((size_t)word_count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (!contains_substring(words[i], filter)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(words[i]);
            char *new_word = (char *)malloc(len + 1);
            if (new_word == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(new_word, words[i]);
            result[count] = new_word;
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    char **resized = (char **)realloc(result, (size_t)count * sizeof(char *));
    if (resized == NULL) {
        for (int i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
        *result_count = 0;
        return NULL;
    }

    *result_count = count;
    return resized;
}

static void free_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *initial_words[] = {
        "Red",
        "",
        "Green",
        "Orange",
        "White",
        "Red &",
        "Orange+"
    };
    int initial_count = (int)(sizeof(initial_words) / sizeof(initial_words[0]));

    char **word_list = (char **)malloc((size_t)initial_count * sizeof(char *));
    if (word_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < initial_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(initial_words[i]);
        char *new_word = (char *)malloc(len + 1);
        if (new_word == NULL) {
            for (int j = 0; j < i; j++) {
                free(word_list[j]);
            }
            free(word_list);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(new_word, initial_words[i]);
        word_list[i] = new_word;
    }

    int result_count = 0;
    char **filtered = remove_words(word_list, initial_count, "", &result_count);

    if (filtered != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", filtered[i]);
        }
        free_words(filtered, result_count);
    } else {
        printf("No words found after filtering\n");
    }

    free_words(word_list, initial_count);

    return EXIT_SUCCESS;
}