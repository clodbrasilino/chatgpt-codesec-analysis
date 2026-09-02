#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string(const char *input, const char *delimiters) {
    int nmatch = 10;
    regmatch_t pmatch[nmatch];
    regex_t regex;
    char *pattern = (char *)malloc(strlen(delimiters) + 3);
    if (pattern == NULL) {
        return;
    }
    sprintf(pattern, "[%s]+", delimiters);

    int reti = regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE);
    if (reti != 0) {
        free(pattern);
        return;
    }

    const size_t input_length = strlen(input);
    char *output = (char *)malloc(input_length + 1);
    if (output == NULL) {
        regfree(&regex);
        free(pattern);
        return;
    }
    strcpy(output, input);

    size_t start, end;
    int count = 0;
    do {
        reti = regexec(&regex, output + count, nmatch, pmatch, 0);
        if (!reti) {
            start = pmatch[0].rm_so;
            if (start != count && start >= 0) {
                end = pmatch[0].rm_eo - 1;
                printf("%.*s\n", (int)(end - count + 1), output + count);
            } else {
                end = count;
            }
            count += end + 1;
        } else {
            break;
        }
    } while (count < input_length);

    if (count < input_length) {
        printf("%s\n", output + count);
    }

    free(output);
    regfree(&regex);
    free(pattern);
}

int main() {
    const char *input = "Hello, world: this is a test";
    const char *delimiters = ",: ";
    split_string(input, delimiters);
    return 0;
}