#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCH_GROUPS 2
#define MAX_INPUT_LEN 4096
#define ERRBUF_LEN 256

static void print_regex_error(int ret, const regex_t *regex, const char *context)
{
    char errbuf[ERRBUF_LEN];
    size_t needed;

    memset(errbuf, 0, sizeof(errbuf));
    needed = regerror(ret, regex, errbuf, sizeof(errbuf) - 1U);
    if (needed >= sizeof(errbuf)) {
        errbuf[sizeof(errbuf) - 1U] = '\0';
    }
    errbuf[sizeof(errbuf) - 1U] = '\0';
    fprintf(stderr, "%s: %s\n", context, errbuf);
}

static char *extract_quoted_value(const regex_t *regex, const char *input,
                                  size_t input_len, size_t *offset)
{
    regmatch_t matches[MAX_MATCH_GROUPS];
    char *result = NULL;
    int ret;
    size_t remaining;

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

    ret = regexec(regex, input + *offset, MAX_MATCH_GROUPS, matches, 0);
    if (ret == 0) {
        regoff_t start = matches[1].rm_so;
        regoff_t end = matches[1].rm_eo;

        if (start >= 0 && end >= start && (size_t)end <= remaining) {
            size_t len = (size_t)(end - start);

            if (len < MAX_INPUT_LEN) {
                result = malloc(len + 1U);
                if (result != NULL) {
                    if (len > 0U &&
                        (size_t)start <= remaining &&
                        len <= remaining - (size_t)start) {
                        memcpy(result, input + *offset + (size_t)start, len);
                        result[len] = '\0';
                    } else if (len == 0U) {
                        result[0] = '\0';
                    } else {
                        free(result);
                        return NULL;
                    }
                    if (matches[0].rm_eo >= 0 &&
                        (size_t)matches[0].rm_eo <= remaining) {
                        *offset += (size_t)matches[0].rm_eo;
                    } else {
                        *offset = input_len;
                    }
                } else {
                    fprintf(stderr, "Memory allocation failed\n");
                }
            }
        }
    } else if (ret != REG_NOMATCH) {
        print_regex_error(ret, regex, "Regex execution failed");
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