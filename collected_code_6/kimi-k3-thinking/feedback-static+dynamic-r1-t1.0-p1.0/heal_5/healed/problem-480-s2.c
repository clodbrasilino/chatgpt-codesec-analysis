#include <stdio.h>
#include <stdlib.h>

#define ASCII_RANGE 256
#define BUFFER_SIZE 1024
#define MAX_DISCARD_COUNT 1048576UL

static size_t safe_strnlen(const char *s, size_t maxlen)
{
    size_t i;

    if (s == NULL) {
        return 0;
    }

    for (i = 0; i < maxlen; i++) {
        if (s[i] == '\0') {
            break;
        }
    }

    return i;
}

char find_max_occurring_char(const char *str, size_t len)
{
    size_t counts[ASCII_RANGE] = {0};
    size_t i;
    char max_char;
    size_t max_count;

    if (str == NULL || len == 0) {
        return '\0';
    }

    for (i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    max_char = str[0];
    max_count = counts[(unsigned char)str[0]];

    for (i = 1; i < len; i++) {
        if (counts[(unsigned char)str[i]] > max_count) {
            max_count = counts[(unsigned char)str[i]];
            max_char = str[i];
        }
    }

    return max_char;
}

static int discard_remaining_input(void)
{
    char *discard_buffer;
    size_t discarded = 0;

    discard_buffer = malloc(BUFFER_SIZE);
    if (discard_buffer == NULL) {
        return -1;
    }

    while (fgets(discard_buffer, BUFFER_SIZE, stdin) != NULL) {
        size_t chunk_len = safe_strnlen(discard_buffer, BUFFER_SIZE);

        if (chunk_len > MAX_DISCARD_COUNT - discarded) {
            free(discard_buffer);
            return -1;
        }
        discarded += chunk_len;

        if (discarded >= MAX_DISCARD_COUNT) {
            free(discard_buffer);
            return -1;
        }

        if (chunk_len > 0 && discard_buffer[chunk_len - 1] == '\n') {
            free(discard_buffer);
            return 0;
        }
    }

    free(discard_buffer);
    return 0;
}

int main(void)
{
    char *buffer;
    char result;
    size_t len;

    buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    len = safe_strnlen(buffer, BUFFER_SIZE);

    if (len >= BUFFER_SIZE) {
        fprintf(stderr, "Input is not properly null-terminated\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else if (len == BUFFER_SIZE - 1) {
        if (discard_remaining_input() != 0) {
            fprintf(stderr, "Error while discarding excess input\n");
        }
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (len == 0) {
        fprintf(stderr, "Empty string provided\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    result = find_max_occurring_char(buffer, len);

    if (result == '\0') {
        fprintf(stderr, "Could not determine maximum occurring character\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Maximum occurring character: '%c'\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}