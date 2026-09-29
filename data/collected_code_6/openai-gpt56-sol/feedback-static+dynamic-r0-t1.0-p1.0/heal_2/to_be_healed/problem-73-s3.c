#include <errno.h>
#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_tokens(char **tokens, size_t count)
{
    size_t i;

    if (tokens == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(tokens[i]);
    }

    free(tokens);
}

static int append_token(char ***tokens, size_t *count, size_t *capacity,
                        const char *start, size_t length)
{
    char *token;

    if (tokens == NULL || count == NULL || capacity == NULL ||
        (start == NULL && length != 0) || *count > *capacity) {
        return EINVAL;
    }

    if (length == SIZE_MAX) {
        return EOVERFLOW;
    }

    if (*count == *capacity) {
        size_t new_capacity;
        char **resized;

        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return EOVERFLOW;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*resized)) {
            return EOVERFLOW;
        }

        resized = realloc(*tokens, new_capacity * sizeof(*resized));
        if (resized == NULL) {
            return ENOMEM;
        }

        *tokens = resized;
        *capacity = new_capacity;
    }

    token = malloc(length + 1);
    if (token == NULL) {
        return ENOMEM;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, start, length);
    }
    token[length] = '\0';

    (*tokens)[*count] = token;
    ++*count;

    return 0;
}

static int split_regex(const char *input, size_t input_length,
                       const char *delimiter_pattern,
                       char ***result, size_t *result_count)
{
    regex_t regex;
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t offset = 0;
    int status;
    int regex_status;

    if (input == NULL || delimiter_pattern == NULL ||
        result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0;

    if (memchr(input, '\0', input_length) != NULL) {
        return EINVAL;
    }

    regex_status = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (regex_status != 0) {
        return EINVAL;
    }

    while (offset <= input_length) {
        regmatch_t match;

#ifdef REG_STARTEND
        match.rm_so = 0;
        match.rm_eo = (regoff_t)(input_length - offset);

        if ((size_t)match.rm_eo != input_length - offset) {
            status = EOVERFLOW;
            goto failure;
        }

        regex_status = regexec(&regex, input + offset, 1, &match,
                               REG_STARTEND);
#else
        regex_status = regexec(&regex, input + offset, 1, &match, 0);
#endif

        if (regex_status == REG_NOMATCH) {
            status = append_token(&tokens, &count, &capacity,
                                  input + offset, input_length - offset);
            if (status != 0) {
                goto failure;
            }
            break;
        }

        if (regex_status != 0 || match.rm_so < 0 || match.rm_eo < 0 ||
            match.rm_eo <= match.rm_so) {
            status = EINVAL;
            goto failure;
        }

        if ((size_t)match.rm_so > input_length - offset ||
            (size_t)match.rm_eo > input_length - offset) {
            status = EINVAL;
            goto failure;
        }

        status = append_token(&tokens, &count, &capacity, input + offset,
                              (size_t)match.rm_so);
        if (status != 0) {
            goto failure;
        }

        offset += (size_t)match.rm_eo;
    }

    regfree(&regex);
    *result = tokens;
    *result_count = count;
    return 0;

failure:
    regfree(&regex);
    free_tokens(tokens, count);
    return status;
}

int main(void)
{
    static const char input[] = "alpha,beta;gamma delta|epsilon";
    static const char delimiters[] = "[,;|[:space:]]+";
    char **tokens = NULL;
    size_t count = 0;
    size_t i;
    int status;

    status = split_regex(input, sizeof(input) - 1, delimiters,
                         &tokens, &count);
    if (status != 0) {
        fprintf(stderr, "Failed to split string: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (printf("%s\n", tokens[i]) < 0) {
            free_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}