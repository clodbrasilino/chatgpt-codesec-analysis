#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_adverbs(const char *sentence)
{
    static const char pattern[] = "(^|[^[:alnum:]_])([[:alpha:]]+ly)([^[:alnum:]_]|$)";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    size_t length;
    int result;
    int count = 0;

    if (sentence == NULL) {
        return -1;
    }

    length = strlen(sentence);
    result = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (result != 0) {
        char error_message[256];

        regerror(result, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return -1;
    }

    while (offset <= length) {
        result = regexec(&regex, sentence + offset, 4, matches, 0);
        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            char error_message[256];

            regerror(result, &regex, error_message, sizeof(error_message));
            fprintf(stderr, "Regex matching failed: %s\n", error_message);
            regfree(&regex);
            return -1;
        }

        if (matches[2].rm_so < 0 || matches[2].rm_eo < matches[2].rm_so) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return -1;
        }

        {
            size_t start = offset + (size_t)matches[2].rm_so;
            size_t end = offset + (size_t)matches[2].rm_eo;
            size_t word_length = end - start;

            printf("%.*s: position %zu\n",
                   (int)word_length,
                   sentence + start,
                   start);
            ++count;

            if (end <= offset) {
                fprintf(stderr, "Regex did not advance\n");
                regfree(&regex);
                return -1;
            }

            offset = end;
        }
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    char *sentence = NULL;
    size_t capacity = 0;
    ssize_t characters_read;
    int count;

    characters_read = getline(&sentence, &capacity, stdin);
    if (characters_read < 0) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fprintf(stderr, "No input provided\n");
        }
        free(sentence);
        return EXIT_FAILURE;
    }

    if (characters_read > 0 && sentence[characters_read - 1] == '\n') {
        sentence[characters_read - 1] = '\0';
    }

    count = find_adverbs(sentence);
    free(sentence);

    if (count < 0) {
        return EXIT_FAILURE;
    }

    printf("Total adverbs: %d\n", count);
    return EXIT_SUCCESS;
}