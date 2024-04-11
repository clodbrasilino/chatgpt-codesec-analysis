#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char* remove_non_alnum(char* input) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    int inputLength = strlen(input);
    char* result = malloc(inputLength + 1);
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int index = 0;
    reti = regcomp(&regex, "[^a-zA-Z0-9]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    for (int i = 0; i < inputLength; i++) {
        reti = regexec(&regex, &input[i], 0, NULL, 0);
        if (!reti) {
            continue;
        }
        else if (reti == REG_NOMATCH) {
            result[index++] = input[i];
        }
        else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    result[index] = '\0';
    regfree(&regex);
    return result;
}

int main() {
    char* input = "Hello, World! 123";
    char* output = remove_non_alnum(input);
    printf("%s\n", output);
    free(output);
    return 0;
}