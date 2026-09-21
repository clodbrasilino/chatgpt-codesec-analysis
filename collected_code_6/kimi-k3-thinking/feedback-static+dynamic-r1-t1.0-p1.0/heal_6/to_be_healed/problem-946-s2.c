#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHARSET_SIZE 256
#define INPUT_CHUNK_SIZE 1024

static void count_elements(const char *text, size_t *counts, size_t counts_size)
{
    if (counts == NULL || counts_size == 0) {
        return;
    }

    for (size_t i = 0; i < counts_size; i++) {
        counts[i] = 0;
    }

    if (text == NULL) {
        return;
    }

    for (size_t i = 0; text[i] != '\0'; i++) {
        size_t index = (size_t)(unsigned char)text[i];
        if (index < counts_size) {
            counts[index]++;
        }
    }
}

static size_t find_max_count(const size_t *counts, size_t counts_size)
{
    size_t max = 0;

    if (counts == NULL) {
        return 0;
    }

    for (size_t i = 0; i < counts_size; i++) {
        if (counts[i] > max) {
            max = counts[i];
        }
    }

    return max;
}

int find_most_common_elements(const char *text)
{
    size_t *counts;
    size_t max_count;

    if (text == NULL) {
        fprintf(stderr, "Error: input text is NULL.\n");
        return -1;
    }

    counts = calloc(CHARSET_SIZE, sizeof *counts);
    if (counts == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return -1;
    }

    count_elements(text, counts, CHARSET_SIZE);
    max_count = find_max_count(counts, CHARSET_SIZE);

    if (max_count == 0) {
        printf("The text is empty; no elements found.\n");
    } else {
        printf("Most common element(s) (count = %zu):\n", max_count);
        for (size_t i = 0; i < CHARSET_SIZE; i++) {
            if (counts[i] == max_count) {
                if (i >= 32 && i <= 126) {
                    printf("  '%c' : %zu\n", (int)i, counts[i]);
                } else {
                    printf("  0x%02zX : %zu\n", i, counts[i]);
                }
            }
        }
    }

    free(counts);
    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || *buffer == NULL || *capacity == 0) {
        return -1;
    }

    if (*capacity > SIZE_MAX / 2) {
        return -1;
    }

    new_capacity = *capacity * 2;
    if (new_capacity < INPUT_CHUNK_SIZE || new_capacity <= *capacity) {
        return -1;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static char *read_line(FILE *stream)
{
    size_t capacity = INPUT_CHUNK_SIZE;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length >= capacity - 1) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return NULL;
            }
        }
        buffer[length++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *buffer;

    printf("Enter text: ");
    fflush(stdout);

    buffer = read_line(stdin);
    if (buffer == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (find_most_common_elements(buffer) != 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}