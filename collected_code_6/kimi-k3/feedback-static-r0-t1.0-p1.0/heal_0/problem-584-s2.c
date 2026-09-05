#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_adverbs(const char *sentence) {
    regex_t regex;
    regmatch_t match;
    const char *cursor = sentence;
    int offset = 0;
    int ret;
    int found = 0;

    if (sentence == NULL) {
        fprintf(stderr, "Error: sentence is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, "[A-Za-z]+ly", REG_EXTENDED);
    if (ret != 0) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            char errbuf[256];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        int start = offset + (int)match.rm_so;
        int end = offset + (int)match.rm_eo;
        int length = (int)(match.rm_eo - match.rm_so);

        printf("Adverb: %.*s | Position: %d to %d\n",
               length, cursor + match.rm_so, start, end - 1);

        found = 1;
        offset += (int)match.rm_eo;
        cursor += match.rm_eo;

        if (match.rm_eo == 0) {
            cursor++;
            offset++;
            if (*cursor == '\0') {
                break;
            }
        }
    }

    if (!found) {
        printf("No adverbs found.\n");
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    char sentence[1024];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }

    if (find_adverbs(sentence) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}