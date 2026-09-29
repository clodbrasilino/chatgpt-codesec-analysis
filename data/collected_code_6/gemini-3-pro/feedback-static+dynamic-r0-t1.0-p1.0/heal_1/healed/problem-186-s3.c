#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void search_literals(const char *text, const char *pattern) {
    if (text == NULL || pattern == NULL) {
        return;
    }

    regex_t regex;
    int reti;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti != 0) {
        return;
    }

    reti = regexec(&regex, text, 0, NULL, 0);
    if (!reti) {
        printf("Match found.\n");
    } else if (reti == REG_NOMATCH) {
        printf("No match.\n");
    } else {
        size_t errbuf_size = regerror(reti, &regex, NULL, 0);
        char *msgbuf = malloc(errbuf_size);
        if (msgbuf != NULL) {
            regerror(reti, &regex, msgbuf, errbuf_size);
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            free(msgbuf);
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog.";
    const char *pattern = "(fox|dog)";

    search_literals(text, pattern);

    return EXIT_SUCCESS;
}