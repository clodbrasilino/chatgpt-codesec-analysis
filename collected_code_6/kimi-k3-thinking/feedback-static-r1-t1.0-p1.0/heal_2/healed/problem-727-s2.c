#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_INPUT_LENGTH (1024U * 1024U)

static size_t bounded_strnlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static int bounded_copy(char *dest, size_t dest_capacity, size_t dest_used,
                        const char *src, size_t count)
{
    size_t i;

    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (dest_used > dest_capacity || count > dest_capacity - dest_used) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        dest[dest_used + i] = src[i];
    }
    return 0;
}

static void report_regex_error(int errcode, regex_t *regex, const char *prefix)
{
    size_t errbuf_size;
    char *errbuf;

    errbuf_size = regerror(errcode, regex, NULL, 0);
    if (errbuf_size == 0) {
        fprintf(stderr, "%s: error code %d\n", prefix, errcode);
        return;
    }
    errbuf = malloc(errbuf_size);
    if (errbuf == NULL) {
        fprintf(stderr, "%s: error code %d\n", prefix, errcode);
        return;
    }
    regerror(errcode, regex, errbuf, errbuf_size);
    errbuf[errbuf_size - 1] = '\0';
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
    free(errbuf);
}

int remove_non_alnum(const char *input, char **output)
{
    regex_t regex;
    regmatch_t pmatch[1];
    char *result;
    size_t input_len;
    size_t out_capacity;
    size_t pos;
    size_t out_pos;
    size_t copy_len;
    int ret;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    input_len = bounded_strnlen(input, MAX_INPUT_LENGTH);
    if (input_len >= MAX_INPUT_LENGTH) {
        fprintf(stderr, "Input is not null-terminated within %u bytes.\n",
                (unsigned int)MAX_INPUT_LENGTH);
        return -1;
    }

    ret = regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED);
    if (ret != 0) {
        report_regex_error(ret, &regex, "regcomp failed");
        return -1;
    }

    out_capacity = input_len + 1;
    result = malloc(out_capacity);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        regfree(&regex);
        return -1;
    }

    pos = 0;
    out_pos = 0;

    while (pos < input_len) {
        ret = regexec(&regex, input + pos, 1, pmatch, 0);
        if (ret == REG_NOMATCH) {
            copy_len = input_len - pos;
            if (bounded_copy(result, out_capacity - 1, out_pos,
                             input + pos, copy_len) != 0) {
                fprintf(stderr, "Output buffer overflow prevented.\n");
                free(result);
                regfree(&regex);
                return -1;
            }
            out_pos += copy_len;
            break;
        }
        if (ret != 0) {
            report_regex_error(ret, &regex, "regexec failed");
            free(result);
            regfree(&regex);
            return -1;
        }
        if (pmatch[0].rm_so < 0 || pmatch[0].rm_eo <= pmatch[0].rm_so ||
            (size_t)pmatch[0].rm_eo > input_len - pos) {
            fprintf(stderr, "Invalid regex match offsets.\n");
            free(result);
            regfree(&regex);
            return -1;
        }
        copy_len = (size_t)pmatch[0].rm_so;
        if (bounded_copy(result, out_capacity - 1, out_pos,
                         input + pos, copy_len) != 0) {
            fprintf(stderr, "Output buffer overflow prevented.\n");
            free(result);
            regfree(&regex);
            return -1;
        }
        out_pos += copy_len;
        pos += (size_t)pmatch[0].rm_eo;
    }

    result[out_pos] = '\0';
    *output = result;

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "Hello, World! 123 @#$%^&* C_Prog-2024";
    char *cleaned = NULL;

    if (remove_non_alnum(input, &cleaned) != 0) {
        fprintf(stderr, "Failed to remove non-alphanumeric characters.\n");
        return EXIT_FAILURE;
    }

    if (cleaned == NULL) {
        fprintf(stderr, "Unexpected NULL result.\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    cleaned = NULL;

    return EXIT_SUCCESS;
}