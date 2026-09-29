#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  */

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
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(list[i]);
            new_list[new_size] = malloc(len + 1);
            if (new_list[new_size] == NULL) {
                for (size_t k = 0; k < new_size; k++) {
                    free(new_list[k]);
                }
                free(new_list);
                return NULL;
            }
            snprintf(new_list[new_size], len + 1, "%s", list[i]);
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
    size_t size = 0;
    char* buffer = malloc(capacity);
    if (!buffer) return NULL;
    int c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (size + 1 >= capacity) {
            capacity *= 2;
            char* temp = realloc(buffer, capacity);
            if (!temp) { free(buffer); return NULL; }
            buffer = temp;
        }
        buffer[size++] = (char)c;
    }
    if (size == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }
    if (size + 1 >= capacity) {
        char* temp = realloc(buffer, capacity + 1);
        if (!temp) { free(buffer); return NULL; }
        buffer = temp;
    }
    buffer[size] = '\0';
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
    size_t alloc_size = max_words > 0 ? max_words : 1;
    char** words = malloc(alloc_size * sizeof(char*));
    if (!words) return NULL;
    size_t count = 0;
    char* token = strtok(line, " ,[]\"'\n\r\t");
    while (token != NULL && count < max_words) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(token);
        words[count] = malloc(len + 1);
        if (!words[count]) {
            for (size_t i = 0; i < count; i++) free(words[i]);
            free(words);
            return NULL;
        }
        snprintf(words[count], len + 1, "%s", token);
        count++;
        token = strtok(NULL, " ,[]\"'\n\r\t");
    }
    *out_size = count;
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
        if (!line2) { free(line1); return EXIT_FAILURE; }
        list = parse_n_words(line2, n, &list_size);
        free(line2);
        
        char* line3 = read_line();
        if (!line3) { free(line1); return EXIT_FAILURE; }
        
        errno = 0;
        long m_long = strtol(line3, NULL, 10);
        if (errno == ERANGE || m_long < 0) {
            free(line1); free(line3); return EXIT_FAILURE;
        }
        size_t m = (size_t)m_long;
        
        char* line4 = read_line();
        if (!line4) { free(line1); free(line3); return EXIT_FAILURE; }
        to_remove = parse_n_words(line4, m, &remove_size);
        free(line3);
        free(line4);
    } else {
        list = parse_n_words(line1, 1024, &list_size);
        char* line2 = read_line();
        if (line2) {
            to_remove = parse_n_words(line2, 1024, &remove_size);
            free(line2);
        } else {
            to_remove = malloc(1 * sizeof(char*));
            if (!to_remove) {
                free_words(list, list_size);
                free(line1);
                return EXIT_FAILURE;
            }
            remove_size = 0;
        }
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
    printf("]");

    free_words(list, list_size);
    free_words(to_remove, remove_size);
    free_words(new_list, new_size);

    return EXIT_SUCCESS;
}