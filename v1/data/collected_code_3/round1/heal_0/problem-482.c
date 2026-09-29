#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_sequences(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, "[A-Z][a-z]*", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    regmatch_t matches[1];
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        char output[100];
        strncpy(output, &str[start], end - start);
        output[end - start] = '\0';
        printf("%s\n", output);
        str += end;
    }

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    find_sequences(str);
    return 0;
}