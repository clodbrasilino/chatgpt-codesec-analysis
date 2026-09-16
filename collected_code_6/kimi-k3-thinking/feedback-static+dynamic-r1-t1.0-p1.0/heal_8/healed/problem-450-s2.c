#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void free_strings(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(strings[i]);
    }

    free(strings);
}

char **extract_strings(const char *const *strings, size_t count, size_t size, size_t *out_count)
{
    char **result;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (strings == NULL || count == 0) {
        return NULL;
    }

    result = calloc(count, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            continue;
        }

        len = strlen(strings[i]);
        if (len != size) {
            continue;
        }

        result[*out_count] = malloc(len + 1);
        if (result[*out_count] == NULL) {
            free_strings(result, *out_count);
            *out_count = 0;
            return NULL;
        }

        memcpy(result[*out_count], strings[i], len + 1);
        (*out_count)++;
    }

    return result;
}

int parse_number(const char *s, size_t *out)
{
    size_t value = 0;

    if (s == NULL || *s == '\0') {
        return 0;
    }

    while (*s != '\0') {
        size_t digit;

        if (*s < '0' || *s > '9') {
            return 0;
        }

        digit = (size_t)(*s - '0');
        if (value > (SIZE_MAX - digit) / 10) {
            return 0;
        }

        value = value * 10 + digit;
        s++;
    }

    if (out != NULL) {
        *out = value;
    }

    return 1;
}

int add_token(char ***values, size_t *count, size_t *capacity, const char *token)
{
    char *copy;
    size_t len;

    if (values == NULL || count == NULL || capacity == NULL || token == NULL) {
        return 0;
    }

    if (*count == *capacity) {
        size_t new_capacity;
        char **new_values;

        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*new_values)) {
            return 0;
        }

        new_values = realloc(*values, new_capacity * sizeof(*new_values));
        if (new_values == NULL) {
            return 0;
        }

        *values = new_values;
        *capacity = new_capacity;
    }

    len = strlen(token);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return 0;
    }

    memcpy(copy, token, len + 1);
    (*values)[*count] = copy;
    (*count)++;

    return 1;
}

int add_tokens(char ***values, size_t *count, size_t *capacity, const char *text)
{
    static const char delimiters[] = " \t\n\r\f\v[](){}',\"";
    char *dup;
    char *tok;
    size_t len;
    int ok = 1;

    if (values == NULL || count == NULL || capacity == NULL) {
        return 0;
    }

    if (text == NULL) {
        return 1;
    }

    len = strlen(text);
    dup = malloc(len + 1);
    if (dup == NULL) {
        return 0;
    }
    memcpy(dup, text, len + 1);

    for (tok = strtok(dup, delimiters); tok != NULL; tok = strtok(NULL, delimiters)) {
        if (!add_token(values, count, capacity, tok)) {
            ok = 0;
            break;
        }
    }

    free(dup);
    return ok;
}

int main(int argc, char **argv)
{
    char **values = NULL;
    size_t count = 0;
    size_t capacity = 0;
    char **extracted = NULL;
    size_t extracted_count = 0;
    size_t size = 0;
    size_t size_index = 0;
    size_t i;
    int size_found = 0;
    int ok = 1;

    if (argc > 1) {
        for (i = 1; i < (size_t)argc; i++) {
            if (!add_tokens(&values, &count, &capacity, argv[i])) {
                ok = 0;
                break;
            }
        }
    } else {
        char line[4096];

        while (fgets(line, sizeof(line), stdin) != NULL) {
            if (!add_tokens(&values, &count, &capacity, line)) {
                ok = 0;
                break;
            }
        }
    }

    if (!ok) {
        printf("[]\n");
        fflush(stdout);
        free_strings(values, count);
        return EXIT_FAILURE;
    }

    if (count > 0 && parse_number(values[count - 1], NULL)) {
        size_index = count - 1;
        size_found = 1;
    } else if (count > 0 && parse_number(values[0], NULL)) {
        size_index = 0;
        size_found = 1;
    } else {
        for (i = 0; i < count; i++) {
            if (parse_number(values[i], NULL)) {
                size_index = i;
                size_found = 1;
                break;
            }
        }
    }

    if (size_found) {
        parse_number(values[size_index], &size);
    }

    if (size_found && count > 1) {
        char **candidates = malloc((count - 1) * sizeof(*candidates));
        if (candidates == NULL) {
            printf("[]\n");
            fflush(stdout);
            free_strings(values, count);
            return EXIT_FAILURE;
        }

        {
            size_t j = 0;
            for (i = 0; i < count; i++) {
                if (i != size_index) {
                    candidates[j++] = values[i];
                }
            }
            extracted = extract_strings((const char *const *)candidates, count - 1, size, &extracted_count);
        }

        free(candidates);

        if (extracted == NULL) {
            extracted_count = 0;
        }
    }

    printf("[");
    for (i = 0; i < extracted_count; i++) {
        printf("%s'%s'", (i == 0) ? "" : ", ", extracted[i]);
    }
    printf("]\n");
    fflush(stdout);

    free_strings(extracted, extracted_count);
    free_strings(values, count);

    return EXIT_SUCCESS;
}