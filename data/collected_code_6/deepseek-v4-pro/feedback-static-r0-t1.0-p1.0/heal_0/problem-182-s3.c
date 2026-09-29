#include <stdio.h>
#include <string.h>
#include <regex.h>

int count_pattern(const char *str, const char *pattern) {
    regex_t regex;
    regmatch_t match;
    int count = 0;
    const char *p = str;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }
    
    while (regexec(&regex, p, 1, &match, 0) == 0) {
        count++;
        p += match.rm_eo;
        if (match.rm_so == match.rm_eo) {
            p++;
        }
        if (*p == '\0') break;
    }
    
    regfree(&regex);
    return count;
}

void analyze_string(const char *str, int *uppercase, int *lowercase, int *special, int *numeric) {
    *uppercase = count_pattern(str, "[A-Z]");
    *lowercase = count_pattern(str, "[a-z]");
    *special = count_pattern(str, "[^a-zA-Z0-9]");
    *numeric = count_pattern(str, "[0-9]");
}

int main(void) {
    char input[1024];
    int uppercase, lowercase, special, numeric;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    analyze_string(input, &uppercase, &lowercase, &special, &numeric);
    
    printf("Uppercase letters: %d\n", uppercase);
    printf("Lowercase letters: %d\n", lowercase);
    printf("Special characters: %d\n", special);
    printf("Numeric values: %d\n", numeric);
    
    return 0;
}