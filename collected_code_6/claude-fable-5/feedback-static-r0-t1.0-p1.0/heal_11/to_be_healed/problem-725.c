#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCH_GROUPS 2
#define MAX_INPUT_LEN 4096
#define ERRBUF_LEN 256

static void print_regex_error(int ret, const regex_t *regex, const char *context)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_LEN];
    size_t written;

    if (context == NULL) {
        context = "Regex error";
    }

    memset(errbuf, 0, sizeof(errbuf));
    written = regerror(ret, regex, errbuf, sizeof(errbuf) - 1U);
    if (written >= sizeof(errbuf)) {
        errbuf[sizeof(errbuf) - 1U] = '\0';
    } else {
        errbuf[written < sizeof(errbuf) ? written : sizeof(errbuf) - 1U] = '\0';
    }
    fprintf(stderr, "%s: %s\n", context, errbuf);
}

static char *extract_quoted_value(const regex_t *regex, const char *input,
                                  size_t input_len, size_t *offset)
{
    regmatch_t matches[MAX_MATCH_GROUPS];
    char *result = NULL;
    int ret;
    size_t remaining;
    regoff_t start;
    regoff_t end;
    size_t len;

    if (regex == NULL || input == NULL || offset == NULL) {
        return NULL;
    }

    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (*offset >= input_len) {
        return NULL;
    }

    remaining = input_len - *offset;

    memset(matches, 0, sizeof(matches));

    ret = regexec(regex, input + *offset, MAX_MATCH_GROUPS, matches, 0);
    if (ret == REG_NOMATCH) {
        return NULL;
    }
    if (ret != 0) {
        print_regex_error(ret, regex, "Regex execution failed");
        return NULL;
    }

    start = matches[1].rm_so;
    end = matches[1].rm_eo;

    if (start < 0 || end < start) {
        return NULL;
    }

    if ((size_t)start > remaining || (size_t)end > remaining) {
        return NULL;
    }

    len = (size_t)(end - start);

    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (len > remaining - (size_t)start) {
        return NULL;
    }

    result = malloc(len + 1U);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    if (len > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, input + *offset + (size_t)start, len);
    }
    result[len] = '\0';

    if (matches[0].rm_eo > 0 && (size_t)matches[0].rm_eo <= remaining) {
        *offset += (size_t)matches[0].rm_eo;
    } else {
        *offset = input_len;
    }

    return result;
}

int main(void)
{
    const char *text = "Name: \"Alice\", City: \"Paris\", Job: \"Engineer\"";
    size_t offset = 0;
    size_t input_len;
    regex_t regex;
    int ret;

    input_len = strnlen(text, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    ret = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", text);

    for (;;) {
        char *value = extract_quoted_value(&regex, text, input_len, &offset);
        if (value == NULL) {
            break;
        }
        printf("Extracted: %s\n", value);
        free(value);
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}