#include <stdio.h>
#include <regex.h>

int endsWithAlphanumeric(const char *string) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[a-zA-Z0-9]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return -1;
    }

    reti = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regex match failed\n");
        return -1;
    }
}

int main() {
    char* myString = "Hello123";
    int result = endsWithAlphanumeric(myString);
    printf("Result: %d\n", result);
    return 0;
}