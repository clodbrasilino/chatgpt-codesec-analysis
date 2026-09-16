#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_adverbs(const char *sentence)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]+ly)([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    int count = 0;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);

    if (result != 0) {
        char message[256];
        regerror(result, &regex, message, sizeof(message));
        fprintf(stderr, "Regex compilation failed: %s\n", message);
        return -1;
    }

    while (sentence[offset] != '\0') {
        result = regexec(&regex, sentence + offset, 4, matches, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            char message[256];
            regerror(result, &regex, message, sizeof(message));
            fprintf(stderr, "Regex execution failed: %s\n", message);
            regfree(&regex);
            return -1;
        }

        if (matches[2].rm_so < 0 || matches[2].rm_eo <= matches[2].rm_so) {
            fprintf(stderr, "Unexpected regex match state\n");
            regfree(&regex);
            return -1;
        }

        size_t start = offset + (size_t)matches[2].rm_so;
        size_t end = offset + (size_t)matches[2].rm_eo;
        size_t length = end - start;

        printf("%.*s: position %zu\n", (int)length, sentence + start, start);
        ++count;
        offset = end;
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    char *sentence = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&sentence, &capacity, stdin);

    if (length < 0) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fprintf(stderr, "No input provided\n");
        }
        free(sentence);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (sentence[length - 1] == '\n' || sentence[length - 1] == '\r')) {
        sentence[--length] = '\0';
    }

    int count = find_adverbs(sentence);
    free(sentence);

    if (count < 0) {
        return EXIT_FAILURE;
    }

    printf("Total adverbs: %d\n", count);
    return EXIT_SUCCESS;
}