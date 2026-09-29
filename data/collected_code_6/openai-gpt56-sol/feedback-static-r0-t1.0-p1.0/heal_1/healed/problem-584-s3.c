#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void print_regex_error(int status, const regex_t *regex, const char *message)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *buffer;

    if (size == 0) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    regerror(status, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

static int find_adverbs(const char *sentence)
{
    static const char pattern[] = "\\b[A-Za-z]+ly\\b";
    regex_t regex;
    regmatch_t match;
    size_t offset = 0;
    int status;

    if (sentence == NULL) {
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (status != 0) {
        print_regex_error(status, &regex, "Regex compilation failed");
        return EXIT_FAILURE;
    }

    while (sentence[offset] != '\0') {
        size_t start;
        size_t end;
        size_t match_length;

        status = regexec(&regex, sentence + offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            print_regex_error(status, &regex, "Regex matching failed");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if ((uintmax_t)match.rm_so > SIZE_MAX - offset ||
            (uintmax_t)match.rm_eo > SIZE_MAX - offset) {
            fprintf(stderr, "Match position is out of range\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        start = offset + (size_t)match.rm_so;
        end = offset + (size_t)match.rm_eo;
        match_length = end - start;

        printf("%.*s: [%zu, %zu)\n",
               match_length > (size_t)INT_MAX ? INT_MAX : (int)match_length,
               sentence + start,
               start,
               end);

        offset = end;
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(void)
{
    char *sentence = NULL;
    size_t capacity = 0;
    ssize_t length;
    int result;

    printf("Enter a sentence: ");
    fflush(stdout);

    length = getline(&sentence, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Failed to read input\n");
        free(sentence);
        return EXIT_FAILURE;
    }

    if (length > 0 && sentence[(size_t)length - 1] == '\n') {
        sentence[(size_t)length - 1] = '\0';
    }

    result = find_adverbs(sentence);
    free(sentence);

    return result;
}