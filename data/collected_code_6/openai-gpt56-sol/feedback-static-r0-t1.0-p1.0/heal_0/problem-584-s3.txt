#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>

static int find_adverbs(const char *sentence)
{
    const char *pattern = "\\b[A-Za-z]+ly\\b";
    regex_t regex;
    regmatch_t match;
    size_t offset = 0U;
    int status;

    if (sentence == NULL) {
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (status != 0) {
        char error_message[256];
        regerror(status, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return EXIT_FAILURE;
    }

    while (sentence[offset] != '\0') {
        status = regexec(&regex, sentence + offset, 1U, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            char error_message[256];
            regerror(status, &regex, error_message, sizeof(error_message));
            fprintf(stderr, "Regex matching failed: %s\n", error_message);
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        {
            size_t start = offset + (size_t)match.rm_so;
            size_t end = offset + (size_t)match.rm_eo;

            printf("%.*s: [%zu, %zu)\n",
                   (int)(end - start),
                   sentence + start,
                   start,
                   end);

            offset = end;
        }
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(void)
{
    char *sentence = NULL;
    size_t capacity = 0U;
    ssize_t length;

    printf("Enter a sentence: ");
    fflush(stdout);

    length = getline(&sentence, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Failed to read input\n");
        free(sentence);
        return EXIT_FAILURE;
    }

    if (length > 0 && sentence[(size_t)length - 1U] == '\n') {
        sentence[(size_t)length - 1U] = '\0';
    }

    if (find_adverbs(sentence) != EXIT_SUCCESS) {
        free(sentence);
        return EXIT_FAILURE;
    }

    free(sentence);
    return EXIT_SUCCESS;
}