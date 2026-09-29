#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

size_t my_strlen(const char* s, size_t max_len) {
    size_t len = 0;
    while (len < max_len && s[len] != '\0') len++;
    return len;
}

char* my_strdup(const char* s) {
    if (!s) return NULL;
    size_t len = my_strlen(s, 1048576);
    char* p = malloc(len + 1);
    if (p) {
        for (size_t i = 0; i <= len; i++) {
            p[i] = s[i];
        }
    }
    return p;
}

char** remove_words(char** list, size_t list_size, char** to_remove, size_t remove_size, size_t* out_size) {
    if (list == NULL || to_remove == NULL || out_size == NULL) {
        return NULL;
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
        for (size_t j = 0; j < remove_size; j++) {
            if (to_remove[j] != NULL && strcmp(list[i], to_remove[j]) == 0) {
                match = 1;
                break;
            }
        }
        if (!match) {
            new_list[new_size] = my_strdup(list[i]);
            if (new_list[new_size] == NULL) {
                for (size_t k = 0; k < new_size; k++) {
                    free(new_list[k]);
                }
                free(new_list);
                return NULL;
            }
            new_size++;
        }
    }
    
    *out_size = new_size;
    new_list[new_size] = NULL;
    
    char** reduced_list = realloc(new_list, (new_size + 1) * sizeof(char*));
    if (reduced_list != NULL) {
        new_list = reduced_list;
    }
    
    return new_list;
}

char* read_line(void) {
    size_t capacity = 1024;
    char* buffer = malloc(capacity);
    if (!buffer) return NULL;
    buffer[0] = '\0';
    size_t size = 0;

    while (fgets(buffer + size, capacity - size, stdin)) {
        size_t chunk_len = my_strlen(buffer + size, capacity - size);
        size += chunk_len;
        
        if (size > 0 && (buffer[size - 1] == '\n' || buffer[size - 1] == '\r')) {
            while (size > 0 && (buffer[size - 1] == '\n' || buffer[size - 1] == '\r')) {
                buffer[--size] = '\0';
            }
            return buffer;
        }
        
        if (size + 2 >= capacity) {
            capacity *= 2;
            char* temp = realloc(buffer, capacity);
            if (!temp) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
    }
    
    if (size == 0) {
        free(buffer);
        return NULL;
    }
    
    return buffer;
}

int is_digit_str(const char* s) {
    if (!s || !*s) return 0;
    for (size_t i = 0; s[i]; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}

char** parse_n_words(char* line, size_t max_words, size_t* out_size) {
    size_t alloc_size = (max_words > 0 ? max_words : 1) + 1;
    char** words = malloc(alloc_size * sizeof(char*));
    if (!words) return NULL;
    size_t count = 0;
    if (line) {
        char* token = strtok(line, " ,[]\"'\n\r\t");
        while (token != NULL && count < max_words) {
            words[count] = my_strdup(token);
            if (!words[count]) {
                for (size_t i = 0; i < count; i++) free(words[i]);
                free(words);
                return NULL;
            }
            count++;
            token = strtok(NULL, " ,[]\"'\n\r\t");
        }
    }
    *out_size = count;
    char** reduced_words = realloc(words, (count + 1) * sizeof(char*));
    if (reduced_words) {
        words = reduced_words;
    }
    words[count] = NULL;
    return words;
}

void free_words(char** words, size_t count) {
    if (words) {
        for (size_t i = 0; i < count; i++) {
            free(words[i]);
        }
        free(words);
    }
}

int main(void) {
    char* line1 = read_line();
    if (!line1) return EXIT_FAILURE;

    char** list = NULL;
    size_t list_size = 0;
    char** to_remove = NULL;
    size_t remove_size = 0;

    if (is_digit_str(line1)) {
        errno = 0;
        long n_long = strtol(line1, NULL, 10);
        if (errno == ERANGE || n_long < 0) {
            free(line1);
            return EXIT_FAILURE;
        }
        size_t n = (size_t)n_long;
        
        char* line2 = read_line();
        if (line2) {
            list = parse_n_words(line2, n, &list_size);
            free(line2);
        } else {
            list = calloc(1, sizeof(char*));
            list_size = 0;
        }
        if (!list) { free(line1); return EXIT_FAILURE; }

        char* line3 = read_line();
        size_t m = 0;
        if (line3) {
            errno = 0;
            long m_long = strtol(line3, NULL, 10);
            if (errno != ERANGE && m_long >= 0) {
                m = (size_t)m_long;
            }
            free(line3);
        }

        char* line4 = read_line();
        if (line4) {
            to_remove = parse_n_words(line4, m, &remove_size);
            free(line4);
        } else {
            to_remove = calloc(1, sizeof(char*));
            remove_size = 0;
        }
        if (!to_remove) { free_words(list, list_size); free(line1); return EXIT_FAILURE; }
    } else {
        list = parse_n_words(line1, 1024, &list_size);
        if (!list) { free(line1); return EXIT_FAILURE; }
        
        char* line2 = read_line();
        if (line2) {
            to_remove = parse_n_words(line2, 1024, &remove_size);
            free(line2);
        } else {
            to_remove = calloc(1, sizeof(char*));
            remove_size = 0;
        }
        if (!to_remove) { free_words(list, list_size); free(line1); return EXIT_FAILURE; }
    }
    free(line1);

    size_t new_size = 0;
    char** new_list = remove_words(list, list_size, to_remove, remove_size, &new_size);

    if (new_list == NULL) {
        free_words(list, list_size);
        free_words(to_remove, remove_size);
        return EXIT_FAILURE;
    }

    printf("[");
    for (size_t i = 0; i < new_size; i++) {
        printf("'%s'", new_list[i]);
        if (i < new_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free_words(list, list_size);
    free_words(to_remove, remove_size);
    free_words(new_list, new_size);

    return EXIT_SUCCESS;
}