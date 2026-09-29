#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_long_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    /* Possible weaknesses found:
     *  The scope of the variable 'word' can be reduced. [variableScope]
     */
    char *word;
    /* Possible weaknesses found:
     *  The scope of the variable 'length' can be reduced. [variableScope]
     */
    size_t length;
    int ret;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[[:alpha:]]{4,}", REG_EXTENDED);
    if (ret != 0) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    cursor = text;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }
        length = (size_t)(match.rm_eo - match.rm_so);
        word = malloc(length + 1);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return -1;
        }
        memcpy(word, cursor + match.rm_so, length);
        word[length] = '\0';
        printf("%s\n", word);
        free(word);
        cursor += match.rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "The quick brown fox jumps over a lazy dog near it";

    if (find_long_words(input) != 0) {
        fprintf(stderr, "Failed to process input string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}