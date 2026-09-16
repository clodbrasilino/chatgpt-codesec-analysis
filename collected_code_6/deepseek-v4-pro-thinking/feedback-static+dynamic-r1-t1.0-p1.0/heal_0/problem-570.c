#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplicate_string(const char *s)
{
    if (s == NULL) {
        return NULL;
    }
    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len + 1);
    return copy;
}

void remove_words(char **words, size_t *count, const char *substr)
{
    if (words == NULL || count == NULL || substr == NULL || *count == 0) {
        return;
    }
    if (substr[0] == '\0') {
        return;
    }
    size_t write = 0;
    size_t i;
    for (i = 0; i < *count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (strstr(words[i], substr) != NULL) {
            free(words[i]);
            words[i] = NULL;
        } else {
            words[write++] = words[i];
        }
    }
    for (i = write; i < *count; i++) {
        words[i] = NULL;
    }
    *count = write;
}

int main(void)
{
    const char *initial[] = { "apple", "banana", "apricot", "cherry", "grape" };
    size_t count = sizeof(initial) / sizeof(initial[0]);
    char **words = malloc(count * sizeof(char *));
    size_t i;
    if (words == NULL) {
        return EXIT_FAILURE;
    }
    for (i = 0; i < count; i++) {
        words[i] = duplicate_string(initial[i]);
        if (words[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return EXIT_FAILURE;
        }
    }
    printf("Before:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
    remove_words(words, &count, "ap");
    printf("After:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
    return EXIT_SUCCESS;
}