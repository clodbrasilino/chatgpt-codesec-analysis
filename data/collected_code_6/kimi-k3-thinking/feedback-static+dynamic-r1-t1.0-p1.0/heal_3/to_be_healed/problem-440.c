#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_ADVERBS 128

typedef struct {
    char *word;
    size_t char_position;
    size_t word_index;
} AdverbEntry;

static const char *common_adverbs[] = {
    "very", "too", "quite", "rather", "almost", "nearly",
    "always", "never", "often", "seldom", "rarely", "sometimes",
    "usually", "frequently", "soon", "now", "then", "here",
    "there", "everywhere", "anywhere", "somewhere", "nowhere",
    "well", "fast", "hard", "just", "even", "still", "yet",
    "again", "also", "indeed", "perhaps", "maybe", "certainly",
    "really", "truly", "surely", "today", "tomorrow", "yesterday",
    "ago", "already", "once", "twice", "enough", "far", "much",
    "so", "however", "therefore", "thus", "hence", "meanwhile"
};

static const char *ly_exceptions[] = {
    "family", "fly", "apply", "reply", "supply", "imply",
    "holy", "lonely", "ugly", "friendly", "lovely", "lively",
    "silly", "jelly", "belly", "ally", "rally", "tally",
    "bully", "chilly", "costly", "elderly", "likely", "orderly",
    "scholarly", "deadly", "oily", "unruly", "wily", "assembly",
    "curly", "dally", "folly", "gully", "hilly", "holly",
    "jolly", "lily", "comply", "multiply", "grisly"
};

static bool ends_with_ly(const char *word)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(word);
    if (len < 3) {
        return false;
    }
    return word[len - 2] == 'l' && word[len - 1] == 'y';
}

static bool matches_word_list(const char *word, const char **list, size_t count)
{
    if (word == NULL || list == NULL) {
        return false;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL && strcmp(word, list[i]) == 0) {
            return true;
        }
    }
    return false;
}

static bool is_adverb(const char *word)
{
    if (word == NULL) {
        return false;
    }

    if (matches_word_list(word, common_adverbs,
                          sizeof(common_adverbs) / sizeof(common_adverbs[0]))) {
        return true;
    }
    if (ends_with_ly(word) &&
        !matches_word_list(word, ly_exceptions,
                           sizeof(ly_exceptions) / sizeof(ly_exceptions[0]))) {
        return true;
    }
    return false;
}

static void free_adverbs(AdverbEntry *results, size_t count)
{
    if (results == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        free(results[i].word);
        results[i].word = NULL;
    }
}

static size_t find_adverbs(const char *sentence, AdverbEntry *results, size_t max_results)
{
    size_t found = 0;
    size_t word_index = 0;
    size_t i = 0;

    if (sentence == NULL || results == NULL || max_results == 0) {
        return 0;
    }

    while (sentence[i] != '\0') {
        if (isalpha((unsigned char)sentence[i])) {
            size_t start = i;
            size_t wlen = 0;
            size_t capacity = 16;
            char *word = malloc(capacity);

            if (word == NULL) {
                return found;
            }

            while (isalpha((unsigned char)sentence[i])) {
                if (wlen + 1 >= capacity) {
                    size_t new_capacity = capacity * 2;
                    char *tmp = realloc(word, new_capacity);

                    if (tmp == NULL) {
                        free(word);
                        return found;
                    }
                    word = tmp;
                    capacity = new_capacity;
                }
                word[wlen] = (char)tolower((unsigned char)sentence[i]);
                wlen++;
                i++;
            }
            word[wlen] = '\0';

            if (wlen > 0) {
                if (is_adverb(word) && found < max_results) {
                    results[found].word = malloc(wlen + 1);

                    if (results[found].word == NULL) {
                        free(word);
                        return found;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(results[found].word, word, wlen + 1);
                    results[found].char_position = start;
                    results[found].word_index = word_index;
                    found++;
                }
                word_index++;
            }

            free(word);
        } else {
            i++;
        }
    }

    return found;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int c;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *tmp = realloc(buffer, new_capacity);

            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        buffer[length] = (char)c;
        length++;
    }

    if (c == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    AdverbEntry results[MAX_ADVERBS];
    char *sentence;
    size_t count;

    memset(results, 0, sizeof(results));

    printf("Enter a sentence: ");
    fflush(stdout);

    sentence = read_line(stdin);
    if (sentence == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (sentence[0] == '\0') {
        fprintf(stderr, "Error: empty sentence provided.\n");
        free(sentence);
        return EXIT_FAILURE;
    }

    count = find_adverbs(sentence, results, MAX_ADVERBS);

    if (count == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Found %zu adverb(s):\n", count);
        for (size_t i = 0; i < count; i++) {
            printf("  \"%s\" -> word #%zu, character offset %zu\n",
                   results[i].word,
                   results[i].word_index + 1,
                   results[i].char_position);
        }
    }

    free_adverbs(results, count);
    free(sentence);

    return EXIT_SUCCESS;
}