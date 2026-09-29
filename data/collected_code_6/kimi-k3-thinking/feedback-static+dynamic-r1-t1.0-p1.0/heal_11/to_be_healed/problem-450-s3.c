#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **extract_strings(const char **list, size_t list_size, size_t extract_size, size_t *out_count);
void free_string_list(char **list, size_t count);
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['practice', 'solution'], got <no output>
  *  test case 2 failed: expected ['exercises'], got <no output>
  *  test case 1 failed: expected ['Python'], got <no output>
  */

char **extract_strings(const char **list, size_t list_size, size_t extract_size, size_t *out_count)
{
    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (list == NULL || list_size == 0) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] != NULL && strlen(list[i]) == extract_size) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    if (count > ((size_t)-1) / sizeof(char *)) {
        return NULL;
    }

    char **result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] == NULL || strlen(list[i]) != extract_size) {
            continue;
        }
        result[j] = malloc(extract_size + 1);
        if (result[j] == NULL) {
            free_string_list(result, j);
            return NULL;
        }
        memcpy(result[j], list[i], extract_size + 1);
        j++;
    }

    *out_count = count;
    return result;
}

void free_string_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

static int is_number(const char *s)
{
    if (s == NULL || *s == '\0') {
        return 0;
    }
    for (const unsigned char *p = (const unsigned char *)s; *p != '\0'; p++) {
        if (!isdigit(*p)) {
            return 0;
        }
    }
    return 1;
}

static int is_delim(int c)
{
    return isspace((unsigned char)c) || c == ',' || c == '[' || c == ']' ||
           c == '(' || c == ')' || c == '{' || c == '}' || c == '\'' ||
           c == '"' || c == '=' || c == ':' || c == ';';
}

static int append_token(char ***tokens, size_t *ntokens, size_t *cap,
                        const char *start, size_t len)
{
    if (len == 0) {
        return 1;
    }

    if (*ntokens == *cap) {
        size_t ncap = (*cap == 0) ? 8 : *cap * 2;
        if (ncap < *cap || ncap > ((size_t)-1) / sizeof(char *)) {
            return 0;
        }
        char **nt = realloc(*tokens, ncap * sizeof(*nt));
        if (nt == NULL) {
            return 0;
        }
        *tokens = nt;
        *cap = ncap;
    }

    char *tok = malloc(len + 1);
    if (tok == NULL) {
        return 0;
    }
    memcpy(tok, start, len);
    tok[len] = '\0';
    (*tokens)[(*ntokens)++] = tok;
    return 1;
}

static int tokenize_string(const char *s, char ***tokens, size_t *ntokens, size_t *cap)
{
    const char *p = s;

    while (*p != '\0') {
        while (*p != '\0' && is_delim((unsigned char)*p)) {
            p++;
        }
        const char *start = p;
        while (*p != '\0' && !is_delim((unsigned char)*p)) {
            p++;
        }
        if (p > start &&
            !append_token(tokens, ntokens, cap, start, (size_t)(p - start))) {
            return 0;
        }
    }
    return 1;
}

static char *read_stream(FILE *fp)
{
    size_t cap = 4096;
    size_t len = 0;
    char *buf = malloc(cap);
    if (buf == NULL) {
        return NULL;
    }

    for (;;) {
        if (cap - len < 2049) {
            if (cap > ((size_t)-1) / 2) {
                free(buf);
                return NULL;
            }
            cap *= 2;
            char *nb = realloc(buf, cap);
            if (nb == NULL) {
                free(buf);
                return NULL;
            }
            buf = nb;
        }
        size_t n = fread(buf + len, 1, 2048, fp);
        len += n;
        if (n < 2048) {
            break;
        }
    }
    buf[len] = '\0';
    return buf;
}

static void free_tokens(char **tokens, size_t ntokens)
{
    if (tokens == NULL) {
        return;
    }
    for (size_t i = 0; i < ntokens; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

static void print_python_string(const char *s)
{
    putchar('\'');
    if (s != NULL) {
        for (const unsigned char *p = (const unsigned char *)s; *p != '\0'; p++) {
            switch (*p) {
            case '\\':
                printf("\\\\");
                break;
            case '\'':
                printf("\\'");
                break;
            case '\n':
                printf("\\n");
                break;
            case '\r':
                printf("\\r");
                break;
            case '\t':
                printf("\\t");
                break;
            default:
                if (*p < 32 || *p > 126) {
                    printf("\\x%02x", (unsigned int)*p);
                } else {
                    putchar(*p);
                }
                break;
            }
        }
    }
    putchar('\'');
}

static void print_result_list(char **list, size_t count)
{
    putchar('[');
    for (size_t i = 0; i < count; i++) {
        if (i != 0) {
            printf(", ");
        }
        print_python_string(list[i]);
    }
    printf("]\n");
}

int main(int argc, char **argv)
{
    char **tokens = NULL;
    size_t ntokens = 0;
    size_t cap = 0;
    int ok = 1;

    if (argc > 1) {
        for (int i = 1; i < argc && ok; i++) {
            ok = tokenize_string(argv[i], &tokens, &ntokens, &cap);
        }
    } else {
        char *input = read_stream(stdin);
        if (input == NULL) {
            ok = 0;
        } else {
            ok = tokenize_string(input, &tokens, &ntokens, &cap);
            free(input);
        }
    }

    if (!ok) {
        free_tokens(tokens, ntokens);
        print_result_list(NULL, 0);
        fflush(stdout);
        return EXIT_SUCCESS;
    }

    if (ntokens == 0) {
        print_result_list(NULL, 0);
        fflush(stdout);
        free(tokens);
        return EXIT_SUCCESS;
    }

    size_t start = 0;
    size_t end = ntokens;
    size_t extract_size = 0;

    if (is_number(tokens[end - 1])) {
        extract_size = (size_t)strtoul(tokens[end - 1], NULL, 10);
        free(tokens[end - 1]);
        tokens[end - 1] = NULL;
        end--;
        if (end > 1 && is_number(tokens[0]) &&
            (size_t)strtoul(tokens[0], NULL, 10) == end - 1) {
            start = 1;
        }
    } else if (is_number(tokens[0])) {
        if (end >= 3 && is_number(tokens[1]) &&
            (size_t)strtoul(tokens[0], NULL, 10) == end - 2) {
            extract_size = (size_t)strtoul(tokens[1], NULL, 10);
            start = 2;
        } else {
            extract_size = (size_t)strtoul(tokens[0], NULL, 10);
            start = 1;
        }
    }

    size_t list_size = end - start;
    const char **list_ptr = (list_size > 0) ? (const char **)(tokens + start) : NULL;

    size_t extracted_count = 0;
    char **extracted = extract_strings(list_ptr, list_size, extract_size, &extracted_count);

    print_result_list(extracted, extracted_count);
    fflush(stdout);

    free_string_list(extracted, extracted_count);
    free_tokens(tokens, end);

    return EXIT_SUCCESS;
}