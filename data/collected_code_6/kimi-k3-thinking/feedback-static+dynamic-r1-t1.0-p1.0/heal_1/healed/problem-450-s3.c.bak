#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **extract_strings(const char **list, size_t list_size, size_t extract_size, size_t *out_count);
void free_string_list(char **list, size_t count);

char **extract_strings(const char **list, size_t list_size, size_t extract_size, size_t *out_count)
{
    char **result;
    size_t count;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (list == NULL) {
        return NULL;
    }

    count = extract_size;
    if (count > list_size) {
        count = list_size;
    }

    if (count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            free_string_list(result, i);
            return NULL;
        }

        len = strlen(list[i]);
        result[i] = malloc(len + 1);
        if (result[i] == NULL) {
            free_string_list(result, i);
            return NULL;
        }
        memcpy(result[i], list[i], len + 1);
    }

    *out_count = count;
    return result;
}

void free_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

static int is_number(const char *s)
{
    char *end;

    if (s == NULL || *s == '\0') {
        return 0;
    }
    (void)strtol(s, &end, 10);
    return end != s && *end == '\0';
}

static int is_delim(int c)
{
    return isspace((unsigned char)c) || c == ',' || c == '[' || c == ']' ||
           c == '(' || c == ')' || c == '{' || c == '}' || c == '\'' || c == '"';
}

static char *read_token(void)
{
    size_t cap = 32;
    size_t len = 0;
    char *buf;
    int c;

    buf = malloc(cap);
    if (buf == NULL) {
        return NULL;
    }

    do {
        c = getchar();
    } while (c != EOF && is_delim(c));

    if (c == EOF) {
        free(buf);
        return NULL;
    }

    while (c != EOF && !is_delim(c)) {
        if (len + 1 >= cap) {
            char *nb;

            cap *= 2;
            nb = realloc(buf, cap);
            if (nb == NULL) {
                free(buf);
                return NULL;
            }
            buf = nb;
        }
        buf[len++] = (char)c;
        c = getchar();
    }
    buf[len] = '\0';

    return buf;
}

static void free_tokens(char **tokens, size_t ntokens)
{
    size_t i;

    if (tokens == NULL) {
        return;
    }
    for (i = 0; i < ntokens; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int main(int argc, char **argv)
{
    char **tokens = NULL;
    size_t ntokens = 0;
    size_t cap = 0;
    int owns_tokens = 0;
    size_t start = 0;
    size_t extract_size = 0;
    size_t list_size;
    size_t extracted_count = 0;
    char **extracted;
    size_t i;

    if (argc > 1) {
        tokens = argv + 1;
        ntokens = (size_t)(argc - 1);
    } else {
        char *tok;

        owns_tokens = 1;
        while ((tok = read_token()) != NULL) {
            if (ntokens == cap) {
                char **nt;

                cap = (cap == 0) ? 8 : cap * 2;
                nt = realloc(tokens, cap * sizeof(*nt));
                if (nt == NULL) {
                    free(tok);
                    free_tokens(tokens, ntokens);
                    return EXIT_FAILURE;
                }
                tokens = nt;
            }
            tokens[ntokens++] = tok;
        }
    }

    if (ntokens == 0) {
        if (owns_tokens) {
            free(tokens);
        }
        return EXIT_SUCCESS;
    }

    if (is_number(tokens[0])) {
        if (ntokens >= 3 && is_number(tokens[1]) &&
            (size_t)strtoul(tokens[0], NULL, 10) == ntokens - 2) {
            extract_size = (size_t)strtoul(tokens[1], NULL, 10);
            start = 2;
        } else {
            extract_size = (size_t)strtoul(tokens[0], NULL, 10);
            start = 1;
        }
    } else if (is_number(tokens[ntokens - 1])) {
        extract_size = (size_t)strtoul(tokens[ntokens - 1], NULL, 10);
        ntokens -= 1;
    } else {
        extract_size = ntokens;
    }

    list_size = ntokens - start;

    extracted = extract_strings((const char **)(tokens + start), list_size,
                                extract_size, &extracted_count);
    if (extracted == NULL && list_size != 0 && extract_size != 0) {
        fprintf(stderr, "String extraction failed\n");
        if (owns_tokens) {
            free_tokens(tokens, ntokens);
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < extracted_count; i++) {
        if (printf("%s\n", extracted[i]) < 0) {
            fprintf(stderr, "Output error\n");
            free_string_list(extracted, extracted_count);
            if (owns_tokens) {
                free_tokens(tokens, ntokens);
            }
            return EXIT_FAILURE;
        }
    }

    free_string_list(extracted, extracted_count);

    if (owns_tokens) {
        free_tokens(tokens, ntokens);
    }

    return EXIT_SUCCESS;
}