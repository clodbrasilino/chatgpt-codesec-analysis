#include <stdio.h>
#include <regex.h>

static int matches_pattern(const char *string)
{
    regex_t regex;
    int compile_result;
    int match_result;

    if (string == NULL) {
        return -1;
    }

    compile_result = regcomp(&regex, "^ab*$", REG_EXTENDED | REG_NOSUB);
    if (compile_result != 0) {
        return -1;
    }

    match_result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (match_result == 0) {
        return 1;
    }

    if (match_result == REG_NOMATCH) {
        return 0;
    }

    return -1;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        fprintf(stderr, "Input is too long.\n");
        return 1;
    }

    int result = matches_pattern(input);

    if (result < 0) {
        fprintf(stderr, "Regex operation failed.\n");
        return 1;
    }

    printf("%s\n", result ? "Match" : "No match");
    return 0;
}