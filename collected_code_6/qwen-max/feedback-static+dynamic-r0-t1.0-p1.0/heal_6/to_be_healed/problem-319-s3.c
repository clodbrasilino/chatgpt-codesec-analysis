#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_five_char_words(const char *string) {
    regex_t regex;
    int reti;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char msgbuf[100];

    if (regcomp(&regex, "\\b\\w{5}\\b", REG_EXTENDED|REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(string);
    if (len < 6) {
        regfree(&regex);
        return;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    if (!reti) {
        regfree(&regex);
        printf("Found a word of five characters\n");
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        return;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        regfree(&regex);
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }
}

int main() {
    const char *input = "This is a test with apple and stone.";
    find_five_char_words(input);
    return 0;
}