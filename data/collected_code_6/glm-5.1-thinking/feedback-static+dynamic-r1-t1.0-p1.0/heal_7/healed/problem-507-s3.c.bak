#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** remove_words(char** list, size_t list_size, char** to_remove, size_t remove_size, size_t* out_size) {
    if (out_size == NULL) {
        return NULL;
    }
    *out_size = 0;

    if (list == NULL) {
        return NULL;
    }
    
    size_t effective_remove_size = 0;
    if (to_remove != NULL) {
        effective_remove_size = remove_size;
    }
    
    char** new_list = malloc((list_size + 1) * sizeof(char*));
    if (new_list == NULL) {
        return NULL;
    }
    
    size_t new_size = 0;
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] == NULL) {
            continue;
        }
        int match = 0;
        for (size_t j = 0; j < effective_remove_size; j++) {
            if (to_remove[j] != NULL && strcmp(list[i], to_remove[j]) == 0) {
                match = 1;
                break;
            }
        }
        if (!match) {
            new_list[new_size] = malloc(strlen(list[i]) + 1);
            if (new_list[new_size] == NULL) {
                for (size_t k = 0; k < new_size; k++) {
                    free(new_list[k]);
                }
                free(new_list);
                return NULL;
            }
            strcpy(new_list[new_size], list[i]);
            new_size++;
        }
    }
    
    *out_size = new_size;
    new_list[new_size] = NULL;
    
    if (new_size < list_size) {
        char** reduced_list = realloc(new_list, (new_size + 1) * sizeof(char*));
        if (reduced_list != NULL) {
            new_list = reduced_list;
        }
    }
    
    return new_list;
}

char* read_line(void) {
    size_t capacity = 256;
    size_t size = 0;
    char* buffer = malloc(capacity);
    if (!buffer) return NULL;
    
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (size + 1 >= capacity) {
            capacity *= 2;
            char* new_buffer = realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[size++] = (char)c;
    }
    if (size == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }
    buffer[size] = '\0';
    return buffer;
}

char** parse_words(const char* line, size_t* count) {
    size_t capacity = 16;
    char** words = malloc(capacity * sizeof(char*));
    if (!words) return NULL;
    *count = 0;
    if (!line) return words;
    
    const char* p = line;
    while (*p) {
        while (*p && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n' || *p == ',' || *p == '[' || *p == ']' || *p == '\'' || *p == '"')) {
            p++;
        }
        if (!*p) break;
        
        const char* start = p;
        while (*p && !(*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n' || *p == ',' || *p == '[' || *p == ']' || *p == '\'' || *p == '"')) {
            p++;
        }
        
        size_t len = p - start;
        if (*count >= capacity) {
            capacity *= 2;
            char** new_words = realloc(words, capacity * sizeof(char*));
            if (!new_words) {
                for (size_t i = 0; i < *count; i++) free(words[i]);
                free(words);
                return NULL;
            }
            words = new_words;
        }
        words[*count] = malloc(len + 1);
        if (!words[*count]) {
            for (size_t i = 0; i < *count; i++) free(words[i]);
            free(words);
            return NULL;
        }
        memcpy(words[*count], start, len);
        words[*count][len] = '\0';
        (*count)++;
    }
    return words;
}

int main(int argc, char** argv) {
    char* line1 = NULL;
    char* line2 = NULL;
    int free_line1 = 0;
    int free_line2 = 0;

    if (argc >= 3) {
        line1 = argv[1];
        line2 = argv[2];
    } else if (argc == 2) {
        line1 = argv[1];
        line2 = read_line();
        if (!line2) {
            line2 = malloc(1);
            if (!line2) {
                return EXIT_FAILURE;
            }
            line2[0] = '\0';
        }
        free_line2 = 1;
    } else {
        line1 = read_line();
        line2 = read_line();
        if (!line1) {
            free(line2);
            return EXIT_FAILURE;
        }
        if (!line2) {
            line2 = malloc(1);
            if (!line2) {
                free(line1);
                return EXIT_FAILURE;
            }
            line2[0] = '\0';
        }
        free_line1 = 1;
        free_line2 = 1;
    }

    size_t list_size = 0;
    char** list = parse_words(line1, &list_size);
    
    size_t remove_size = 0;
    char** to_remove = parse_words(line2, &remove_size);
    
    if (free_line1) {
        free(line1);
    }
    if (free_line2) {
        free(line2);
    }
    
    if (!list || !to_remove) {
        if (list) {
            for (size_t i = 0; i < list_size; i++) free(list[i]);
            free(list);
        }
        if (to_remove) {
            for (size_t i = 0; i < remove_size; i++) free(to_remove[i]);
            free(to_remove);
        }
        return EXIT_FAILURE;
    }
    
    size_t new_size = 0;
    char** new_list = remove_words(list, list_size, to_remove, remove_size, &new_size);
    
    if (new_list) {
        for (size_t i = 0; i < new_size; i++) {
            printf("%s\n", new_list[i]);
            free(new_list[i]);
        }
        free(new_list);
    }
    
    for (size_t i = 0; i < list_size; i++) free(list[i]);
    free(list);
    for (size_t i = 0; i < remove_size; i++) free(to_remove[i]);
    free(to_remove);
    
    return EXIT_SUCCESS;
}