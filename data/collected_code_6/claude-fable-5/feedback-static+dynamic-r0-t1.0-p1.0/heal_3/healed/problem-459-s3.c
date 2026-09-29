#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 256

static void report_regex_error(int ret, const regex_t *regex, const char *prefix)
{
    char errbuf[ERRBUF_SIZE];

    memset(errbuf, 0, sizeof(errbuf));
    regerror(ret, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
}

static char *remove_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t result_pos;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        report_regex_error(ret, &regex, "Regex compilation failed");
        return NULL;
    }

    result = calloc(input_len + 1, sizeof(char));
    if (result == NULL) {
        regfree(&regex);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    result_pos = 0;
    cursor = input;

    while (*cursor != '\0') {
        size_t consumed = (size_t)(cursor - input);

        if (consumed > input_len) {
            fprintf(stderr, "Internal bounds error\n");
            free(result);
            regfree(&regex);
            return NULL;
        }

        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, input_len - consumed);

            if (remaining > input_len - result_pos) {
                fprintf(stderr, "Internal bounds error\n");
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + result_pos, cursor, remaining);
            result_pos += remaining;
            break;
        }
        if (ret != 0) {
            report_regex_error(ret, &regex, "Regex execution failed");
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regex match offsets\n");
            free(result);
            regfree(&regex);
            return NULL;
        }
        if ((size_t)match.rm_so > input_len - result_pos ||
            (size_t)match.rm_eo > input_len - consumed) {
            fprintf(stderr, "Internal bounds error\n");
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + result_pos, cursor, (size_t)match.rm_so);
        result_pos += (size_t)match.rm_so;
        cursor += match.rm_eo;
    }

    if (result_pos > input_len) {
        fprintf(stderr, "Internal bounds error\n");
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[result_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    char *cleaned;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    len = strnlen(buffer, sizeof(buffer));
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[len - 1] = '\0';
        len--;
    }

    cleaned = remove_uppercase(buffer);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned);
    free(cleaned);

    return EXIT_SUCCESS;
}