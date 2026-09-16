#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_words(const char *input, size_t *count)
{
    char *copy;
    char **results;
    char **temp;
    char *token;
    size_t capacity;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    capacity = 8;

    copy = malloc(strlen(input) + 1);
    if (copy == NULL) {
        return NULL;
    }
    strcpy(copy, input);

    results = malloc(capacity * sizeof(char *));
    if (results == NULL) {
        free(copy);
        return NULL;
    }

    token = strtok(copy, " \t\n\r.,;:!?");
    while (token != NULL) {
        char first = (char)tolower((unsigned char)token[0]);
        if (first == 'a' || first == 'e') {
            if (*count == capacity) {
                capacity *= 2;
                temp = realloc(results, capacity * sizeof(char *));
                if (temp == NULL) {
                    for (size_t i = 0; i < *count; i++) {
                        free(results[i]);
                    }
                    free(results);
                    free(copy);
                    *count = 0;
                    return NULL;
                }
                results = temp;
            }
            results[*count] = malloc(strlen(token) + 1);
            if (results[*count] == NULL) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                free(copy);
                *count = 0;
                return NULL;
            }
            strcpy(results[*count], token);
            (*count)++;
        }
        token = strtok(NULL, " \t\n\r.,;:!?");
    }

    free(copy);
    return results;
}

void free_words(char **words, size_t count)
{
    if (words == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void)
{
    const char *text = "An apple and an egg were eaten by everyone at the event.";
    size_t count = 0;
    char **words;

    words = find_words(text, &count);
    if (words == NULL) {
        fprintf(stderr, "Error: could not process the string\n");
        return EXIT_FAILURE;
    }

    printf("Words starting with 'a' or 'e':\n");
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    free_words(words, count);
    return EXIT_SUCCESS;
}