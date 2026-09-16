#include <stdio.h>
#include <regex.h>
#include <string.h>

int search_literals(const char *pattern, const char *text) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB);
    if (ret) {
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    return !ret;
}

int main() {
    const char *text = "This is a sample text with some literals like error and warning.";
    const char *pattern = "error|warning";

    int result = search_literals(pattern, text);
    if (result == 1) {
        printf("Literals found in the text.\n");
    } else if (result == 0) {
        printf("Literals not found in the text.\n");
    } else {
        printf("Failed to compile the regular expression.\n");
    }

    return 0;
}