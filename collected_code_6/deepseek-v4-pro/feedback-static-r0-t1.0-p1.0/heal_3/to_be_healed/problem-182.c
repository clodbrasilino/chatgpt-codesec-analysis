#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct {
    int uppercase_count;
    int lowercase_count;
    int special_count;
    int numeric_count;
} CharCounts;

static void cleanup_regex(regex_t *regex, int count, ...) {
    va_list args;
    /* Possible weaknesses found:
     *  implicit declaration of function 'va_start' [-Wimplicit-function-declaration]
     *  include the header <stdarg.h> or explicitly provide a declaration for 'va_start'
     *  call to undeclared library function 'va_start' with type 'void (struct __va_list_tag *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    va_start(args, count);
    regfree(regex);
    for (int i = 1; i < count; i++) {
        /* Possible weaknesses found:
         *  unexpected type name 'regex_t': expected expression
         *  call to undeclared function 'va_arg'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'va_arg' [-Wimplicit-function-declaration]
         *  expected expression before 'regex_t'
         *  expected expression
         */
        regfree(va_arg(args, regex_t *));
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'va_end' [-Wimplicit-function-declaration]
     *  include the header <stdarg.h> or explicitly provide a declaration for 'va_end'
     *  call to undeclared library function 'va_end' with type 'void (struct __va_list_tag *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    va_end(args);
}

void count_characters(const char *str, CharCounts *counts) {
    regex_t uppercase_regex, lowercase_regex, special_regex, numeric_regex;
    const char *uppercase_pattern = "[A-Z]";
    const char *lowercase_pattern = "[a-z]";
    const char *special_pattern = "[^a-zA-Z0-9]";
    const char *numeric_pattern = "[0-9]";
    int ret;
    char *errbuf = NULL;
    size_t errbuf_size;
    size_t i;
    size_t len;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[2];
    int regex_compiled = 0;

    if (str == NULL || counts == NULL) {
        fprintf(stderr, "Error: NULL pointer argument\n");
        exit(EXIT_FAILURE);
    }

    counts->uppercase_count = 0;
    counts->lowercase_count = 0;
    counts->special_count = 0;
    counts->numeric_count = 0;

    ret = regcomp(&uppercase_regex, uppercase_pattern, REG_EXTENDED);
    if (ret) {
        errbuf_size = regerror(ret, &uppercase_regex, NULL, 0);
        errbuf = (char *)malloc(errbuf_size);
        if (errbuf == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        regerror(ret, &uppercase_regex, errbuf, errbuf_size);
        fprintf(stderr, "Error compiling uppercase regex: %s\n", errbuf);
        free(errbuf);
        exit(EXIT_FAILURE);
    }
    regex_compiled++;

    ret = regcomp(&lowercase_regex, lowercase_pattern, REG_EXTENDED);
    if (ret) {
        errbuf_size = regerror(ret, &lowercase_regex, NULL, 0);
        errbuf = (char *)malloc(errbuf_size);
        if (errbuf == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            regfree(&uppercase_regex);
            exit(EXIT_FAILURE);
        }
        regerror(ret, &lowercase_regex, errbuf, errbuf_size);
        fprintf(stderr, "Error compiling lowercase regex: %s\n", errbuf);
        free(errbuf);
        regfree(&uppercase_regex);
        exit(EXIT_FAILURE);
    }
    regex_compiled++;

    ret = regcomp(&special_regex, special_pattern, REG_EXTENDED);
    if (ret) {
        errbuf_size = regerror(ret, &special_regex, NULL, 0);
        errbuf = (char *)malloc(errbuf_size);
        if (errbuf == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            regfree(&uppercase_regex);
            regfree(&lowercase_regex);
            exit(EXIT_FAILURE);
        }
        regerror(ret, &special_regex, errbuf, errbuf_size);
        fprintf(stderr, "Error compiling special regex: %s\n", errbuf);
        free(errbuf);
        regfree(&uppercase_regex);
        regfree(&lowercase_regex);
        exit(EXIT_FAILURE);
    }
    regex_compiled++;

    ret = regcomp(&numeric_regex, numeric_pattern, REG_EXTENDED);
    if (ret) {
        errbuf_size = regerror(ret, &numeric_regex, NULL, 0);
        errbuf = (char *)malloc(errbuf_size);
        if (errbuf == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            regfree(&uppercase_regex);
            regfree(&lowercase_regex);
            regfree(&special_regex);
            exit(EXIT_FAILURE);
        }
        regerror(ret, &numeric_regex, errbuf, errbuf_size);
        fprintf(stderr, "Error compiling numeric regex: %s\n", errbuf);
        free(errbuf);
        regfree(&uppercase_regex);
        regfree(&lowercase_regex);
        regfree(&special_regex);
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     *  Variable 'regex_compiled' is assigned a value that is never used. [unreadVariable]
     */
    regex_compiled++;

    temp[1] = '\0';
    len = strnlen(str, 4096);

    for (i = 0; i < len; i++) {
        temp[0] = str[i];

        if (regexec(&uppercase_regex, temp, 0, NULL, 0) == 0) {
            counts->uppercase_count++;
        } else if (regexec(&lowercase_regex, temp, 0, NULL, 0) == 0) {
            counts->lowercase_count++;
        } else if (regexec(&numeric_regex, temp, 0, NULL, 0) == 0) {
            counts->numeric_count++;
        } else if (regexec(&special_regex, temp, 0, NULL, 0) == 0) {
            counts->special_count++;
        }
    }

    regfree(&uppercase_regex);
    regfree(&lowercase_regex);
    regfree(&special_regex);
    regfree(&numeric_regex);
}

int main(void) {
    const char *test_string = "Hello World! 123";
    CharCounts counts;

    count_characters(test_string, &counts);

    printf("Input string: %s\n", test_string);
    printf("Uppercase characters: %d\n", counts.uppercase_count);
    printf("Lowercase characters: %d\n", counts.lowercase_count);
    printf("Special characters: %d\n", counts.special_count);
    printf("Numeric characters: %d\n", counts.numeric_count);

    return 0;
}