#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1048576u
#define INITIAL_LINE_CAPACITY 128u

static size_t bounded_length(const char *s, size_t max)
{
    size_t n = 0u;

    if (s == NULL) {
        return 0u;
    }
    while (n < max && s[n] != '\0') {
        n++;
    }
    return n;
}

static int safe_copy(void *dest, size_t dest_capacity, const void *src, size_t count)
{
    unsigned char *d;
    const unsigned char *s;
    size_t i;

    if (dest == NULL || src == NULL) {
        return -1;
    }
    if (count > dest_capacity) {
        return -1;
    }

    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    for (i = 0u; i < count; i++) {
        d[i] = s[i];
    }
    return 0;
}

static int is_delimiter(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static char *next_token(char **cursor)
{
    char *start;
    char *end;

    if (cursor == NULL || *cursor == NULL) {
        return NULL;
    }

    start = *cursor;
    while (*start != '\0' && is_delimiter(*start)) {
        start++;
    }
    if (*start == '\0') {
        *cursor = start;
        return NULL;
    }

    end = start;
    while (*end != '\0' && !is_delimiter(*end)) {
        end++;
    }
    if (*end != '\0') {
        *end = '\0';
        *cursor = end + 1;
    } else {
        *cursor = end;
    }

    return start;
}

char *remove_duplicate_words(const char *str)
{
    size_t len;
    size_t capacity;
    size_t count;
    size_t pos;
    char *copy;
    char *result;
    char **words;
    char *cursor;
    char *token;
    char *shrunk;

    if (str == NULL) {
        return NULL;
    }

    len = bounded_length(str, MAX_INPUT_LENGTH + 1u);
    if (len > MAX_INPUT_LENGTH) {
        return NULL;
    }

    copy = malloc(len + 1u);
    if (copy == NULL) {
        return NULL;
    }
    if (safe_copy(copy, len + 1u, str, len) != 0) {
        free(copy);
        return NULL;
    }
    copy[len] = '\0';

    result = malloc(len + 1u);
    if (result == NULL) {
        free(copy);
        return NULL;
    }
    result[0] = '\0';

    capacity = 16u;
    count = 0u;
    words = malloc(capacity * sizeof(*words));
    if (words == NULL) {
        free(copy);
        free(result);
        return NULL;
    }

    pos = 0u;
    cursor = copy;
    token = next_token(&cursor);
    while (token != NULL) {
        int found = 0;
        size_t i;

        for (i = 0u; i < count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            size_t word_len;
            size_t separator;

            if (count == capacity) {
                size_t new_capacity;
                char **tmp;

                if (capacity > ((size_t)-1) / (2u * sizeof(*words))) {
                    free(words);
                    free(copy);
                    free(result);
                    return NULL;
                }
                new_capacity = capacity * 2u;
                tmp = realloc(words, new_capacity * sizeof(*words));
                if (tmp == NULL) {
                    free(words);
                    free(copy);
                    free(result);
                    return NULL;
                }
                words = tmp;
                capacity = new_capacity;
            }

            words[count++] = token;

            word_len = bounded_length(token, len + 1u);
            separator = (pos > 0u) ? 1u : 0u;
            if (pos > len || separator > len - pos || word_len > len - pos - separator) {
                free(words);
                free(copy);
                free(result);
                return NULL;
            }

            if (pos > 0u) {
                result[pos++] = ' ';
            }
            if (safe_copy(result + pos, (len + 1u) - pos, token, word_len) != 0) {
                free(words);
                free(copy);
                free(result);
                return NULL;
            }
            pos += word_len;
            result[pos] = '\0';
        }

        token = next_token(&cursor);
    }

    free(words);
    free(copy);

    shrunk = realloc(result, pos + 1u);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

static char *read_input_line(FILE *stream)
{
    size_t capacity;
    size_t length;
    char *buffer;
    int c;

    if (stream == NULL) {
        return NULL;
    }

    capacity = INITIAL_LINE_CAPACITY;
    length = 0u;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF && c != '\n' && c != '\r') {
        if (length + 1u >= capacity) {
            size_t new_capacity;
            char *tmp;

            if (capacity >= MAX_INPUT_LENGTH + 1u) {
                break;
            }
            if (capacity > ((size_t)-1) / 2u) {
                new_capacity = MAX_INPUT_LENGTH + 1u;
            } else {
                new_capacity = capacity * 2u;
            }
            if (new_capacity > MAX_INPUT_LENGTH + 1u) {
                new_capacity = MAX_INPUT_LENGTH + 1u;
            }
            if (new_capacity <= capacity) {
                break;
            }
            tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }

        if (length + 1u < capacity) {
            buffer[length++] = (char)c;
        } else {
            break;
        }
    }

    if (c == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int nextc = fgetc(stream);
        if (nextc != '\n' && nextc != EOF) {
            ungetc(nextc, stream);
        }
    }

    if (c == EOF && length == 0u) {
        free(buffer);
        return NULL;
    }

    if (length >= capacity) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(int argc, char **argv)
{
    const char *input;
    char *buffer = NULL;
    char *output;

    if (argc > 1) {
        input = argv[1];
    } else if ((buffer = read_input_line(stdin)) != NULL) {
        input = buffer;
    } else {
        input = "Python Exercises Practice Solution Exercises Practice";
    }

    output = remove_duplicate_words(input);
    free(buffer);

    if (output == NULL) {
        fprintf(stderr, "Error: failed to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    return EXIT_SUCCESS;
}