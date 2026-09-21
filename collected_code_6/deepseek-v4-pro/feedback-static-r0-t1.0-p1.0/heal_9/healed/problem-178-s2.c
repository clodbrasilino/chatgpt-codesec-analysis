#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LITERAL_LENGTH 255

typedef struct {
    char literal[MAX_LITERAL_LENGTH + 1];
    size_t position;
    bool found;
} SearchResult;

static bool copy_literal_safely(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }

    size_t src_len = strnlen(src, dest_size - 1);
    if (src_len == 0) {
        return false;
    }

    if (src_len >= dest_size) {
        return false;
    }

    if (src_len < dest_size) {
        memcpy(dest, src, src_len);
        dest[src_len] = '\0';
        return true;
    }

    return false;
}

SearchResult *search_literals(const char *text, const char **literals, size_t literal_count) {
    if (text == NULL || literals == NULL || literal_count == 0) {
        return NULL;
    }

    SearchResult *results = (SearchResult *)calloc(literal_count, sizeof(SearchResult));
    if (results == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < literal_count; i++) {
        if (literals[i] == NULL) {
            free(results);
            return NULL;
        }

        size_t len = strnlen(literals[i], MAX_LITERAL_LENGTH);
        if (len == 0 || len > MAX_LITERAL_LENGTH) {
            free(results);
            return NULL;
        }

        if (!copy_literal_safely(results[i].literal, sizeof(results[i].literal), literals[i])) {
            free(results);
            return NULL;
        }
        
        const char *pos = strstr(text, results[i].literal);
        if (pos != NULL) {
            results[i].found = true;
            results[i].position = (size_t)(pos - text);
        } else {
            results[i].found = false;
            results[i].position = 0;
        }
    }

    return results;
}

void print_results(const SearchResult *results, size_t count) {
    if (results == NULL) {
        printf("No results to display\n");
        return;
    }

    for (size_t i = 0; i < count; i++) {
        if (results[i].found) {
            printf("'%s' found at position %zu\n", results[i].literal, results[i].position);
        } else {
            printf("'%s' not found\n", results[i].literal);
        }
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *literals[] = {
        "quick",
        "fox",
        "cat",
        "lazy",
        "dog"
    };
    size_t literal_count = sizeof(literals) / sizeof(literals[0]);

    SearchResult *results = search_literals(text, literals, literal_count);
    if (results == NULL) {
        fprintf(stderr, "Error searching literals\n");
        return EXIT_FAILURE;
    }

    print_results(results, literal_count);
    free(results);
    return EXIT_SUCCESS;
}