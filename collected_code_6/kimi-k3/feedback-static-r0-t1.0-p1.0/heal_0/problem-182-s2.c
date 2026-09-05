#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT 1024
#define NUM_PATTERNS 4

typedef struct {
    const char *name;
    const char *pattern;
    regex_t regex;
    int compiled;
} PatternInfo;

static int compile_pattern(PatternInfo *info) {
    int ret = regcomp(&info->regex, info->pattern, REG_EXTENDED);
    if (ret != 0) {
        char error_buf[256];
        regerror(ret, &info->regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "Failed to compile %s pattern: %s\n", info->name, error_buf);
        info->compiled = 0;
        return 0;
    }
    info->compiled = 1;
    return 1;
}

static void cleanup_patterns(PatternInfo *patterns, size_t count) {
    size_t i;
    for (i = 0; i < count; i++) {
        if (patterns[i].compiled) {
            regfree(&patterns[i].regex);
            patterns[i].compiled = 0;
        }
    }
}

static int check_string(const char *input, PatternInfo *patterns, size_t count, int *results) {
    size_t i;
    regmatch_t match;
    
    if (input == NULL || patterns == NULL || results == NULL) {
        return 0;
    }
    
    for (i = 0; i < count; i++) {
        if (!patterns[i].compiled) {
            results[i] = 0;
            continue;
        }
        
        int ret = regexec(&patterns[i].regex, input, 1, &match, 0);
        if (ret == 0) {
            results[i] = 1;
        } else if (ret == REG_NOMATCH) {
            results[i] = 0;
        } else {
            char error_buf[256];
            regerror(ret, &patterns[i].regex, error_buf, sizeof(error_buf));
            fprintf(stderr, "Regex execution failed for %s: %s\n", patterns[i].name, error_buf);
            results[i] = 0;
        }
    }
    
    return 1;
}

int main(void) {
    char input[MAX_INPUT];
    int results[NUM_PATTERNS] = {0};
    size_t i;
    
    PatternInfo patterns[NUM_PATTERNS] = {
        {"Uppercase", "[A-Z]", {0}, 0},
        {"Lowercase", "[a-z]", {0}, 0},
        {"Numeric", "[0-9]", {0}, 0},
        {"Special", "[^A-Za-z0-9[:space:]]", {0}, 0}
    };
    
    printf("Enter a string to analyze: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (len == 0 || (len == 1 && input[0] == '\0')) {
        printf("Empty string provided\n");
        return EXIT_SUCCESS;
    }
    
    for (i = 0; i < NUM_PATTERNS; i++) {
        if (!compile_pattern(&patterns[i])) {
            cleanup_patterns(patterns, NUM_PATTERNS);
            return EXIT_FAILURE;
        }
    }
    
    if (!check_string(input, patterns, NUM_PATTERNS, results)) {
        cleanup_patterns(patterns, NUM_PATTERNS);
        return EXIT_FAILURE;
    }
    
    printf("\nAnalysis results for: \"%s\"\n", input);
    printf("%-15s: %s\n", "Category", "Found");
    printf("%-15s: %s\n", "--------", "-----");
    
    for (i = 0; i < NUM_PATTERNS; i++) {
        printf("%-15s: %s\n", patterns[i].name, results[i] ? "Yes" : "No");
    }
    
    cleanup_patterns(patterns, NUM_PATTERNS);
    
    return EXIT_SUCCESS;
}