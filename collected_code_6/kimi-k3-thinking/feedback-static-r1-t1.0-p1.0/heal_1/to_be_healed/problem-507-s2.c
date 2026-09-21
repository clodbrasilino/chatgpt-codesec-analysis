#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplicate_string(const char *str)
{
    size_t len;
    char *copy;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, len + 1);
    return copy;
}

int add_word(char ***words, size_t *count, const char *word)
{
    char **temp;
    char *copy;

    if (words == NULL || count == NULL || word == NULL) {
        return -1;
    }

    copy = duplicate_string(word);
    if (copy == NULL) {
        return -1;
    }

    temp = realloc(*words, (*count + 1) * sizeof(char *));
    if (temp == NULL) {
        free(copy);
        return -1;
    }

    temp[*count] = copy;
    *words = temp;
    *count += 1;
    return 0;
}

size_t remove_word(char **words, size_t count, const char *target)
{
    size_t i;
    size_t new_count;

    if (words == NULL || target == NULL) {
        return count;
    }

    new_count = 0;
    for (i = 0; i < count; i++) {
        if (words[i] != NULL && strcmp(words[i], target) == 0) {
            free(words[i]);
        } else {
            words[new_count] = words[i];
            new_count++;
        }
    }
    return new_count;
}

void free_words(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void)
{
    char **words = NULL;
    size_t count = 0;
    size_t i;
    const char *initial[] = {"apple", "banana", "cherry", "banana", "date", "grape"};
    const char *remove_list[] = {"banana", "date"};
    size_t initial_size = sizeof(initial) / sizeof(initial[0]);
    size_t remove_size = sizeof(remove_list) / sizeof(remove_list[0]);

    for (i = 0; i < initial_size; i++) {
        if (add_word(&words, &count, initial[i]) != 0) {
            fprintf(stderr, "Error: failed to add word\n");
            free_words(words, count);
            return EXIT_FAILURE;
        }
    }

    printf("Original list:\n");
    for (i = 0; i < count; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    for (i = 0; i < remove_size; i++) {
        count = remove_word(words, count, remove_list[i]);
    }

    printf("List after removal:\n");
    for (i = 0; i < count; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    free_words(words, count);
    return EXIT_SUCCESS;
}