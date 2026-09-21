#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *duplicate_string(const char *str)
{
    size_t len;
    char *copy;

    if (str == NULL) {
        return NULL;
    }

    len = bounded_length(str, MAX_STRING_LENGTH);
    if (len == MAX_STRING_LENGTH) {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, str, len);
    copy[len] = '\0';
    return copy;
}

int add_word(char ***words, size_t *count, const char *word)
{
    char **temp;
    char *copy;

    if (words == NULL || count == NULL || word == NULL) {
        return -1;
    }

    if (*count >= SIZE_MAX / sizeof(char *) - 1) {
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
            words[i] = NULL;
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