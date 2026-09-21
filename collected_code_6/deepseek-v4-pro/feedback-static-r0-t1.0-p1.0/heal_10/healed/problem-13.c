#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 100
#define TOP_N 10

typedef struct {
    char *word;
    int count;
} WordCount;

typedef struct {
    WordCount *items;
    int size;
    int capacity;
} WordCountArray;

static void init_array(WordCountArray *arr) {
    if (arr == NULL) {
        return;
    }
    arr->capacity = INITIAL_CAPACITY;
    arr->size = 0;
    arr->items = (WordCount *)malloc(sizeof(WordCount) * arr->capacity);
    if (arr->items == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

static void free_array(WordCountArray *arr) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        free(arr->items[i].word);
    }
    free(arr->items);
    arr->items = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static void add_word(WordCountArray *arr, const char *word) {
    if (arr == NULL || word == NULL) {
        return;
    }

    size_t word_len = safe_strlen(word, MAX_WORD_LEN);
    if (word_len == 0 || word_len >= MAX_WORD_LEN) {
        return;
    }

    for (int i = 0; i < arr->size; i++) {
        if (strcmp(arr->items[i].word, word) == 0) {
            arr->items[i].count++;
            return;
        }
    }

    if (arr->size >= arr->capacity) {
        if (arr->capacity > INT_MAX / 2) {
            fprintf(stderr, "Capacity overflow\n");
            free_array(arr);
            exit(EXIT_FAILURE);
        }
        int new_capacity = arr->capacity * 2;
        WordCount *new_items = (WordCount *)realloc(arr->items, sizeof(WordCount) * new_capacity);
        if (new_items == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            free_array(arr);
            exit(EXIT_FAILURE);
        }
        arr->items = new_items;
        arr->capacity = new_capacity;
    }

    if (word_len + 1 <= word_len) {
        free_array(arr);
        fprintf(stderr, "Integer overflow detected\n");
        exit(EXIT_FAILURE);
    }

    arr->items[arr->size].word = (char *)malloc(word_len + 1);
    if (arr->items[arr->size].word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_array(arr);
        exit(EXIT_FAILURE);
    }

    memcpy(arr->items[arr->size].word, word, word_len);
    arr->items[arr->size].word[word_len] = '\0';
    arr->items[arr->size].count = 1;
    arr->size++;
}

static int compare_word_counts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wb->count != wa->count) {
        return wb->count - wa->count;
    }
    return strcmp(wa->word, wb->word);
}

static void print_top_words(WordCountArray *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }
    if (n > arr->size) {
        n = arr->size;
    }
    qsort(arr->items, arr->size, sizeof(WordCount), compare_word_counts);
    for (int i = 0; i < n; i++) {
        printf("%s: %d\n", arr->items[i].word, arr->items[i].count);
    }
}

static int is_safe_path(const char *filename) {
    if (filename == NULL) {
        return 0;
    }
    if (strchr(filename, '/') != NULL || strchr(filename, '\\') != NULL) {
        return 0;
    }
    if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
        return 0;
    }
    size_t len = strnlen(filename, MAX_WORD_LEN + 1);
    if (len >= MAX_WORD_LEN) {
        return 0;
    }
    return 1;
}

static FILE *safe_fopen(const char *filename) {
    if (filename == NULL) {
        return NULL;
    }
    
    char resolved_path[PATH_MAX];
    if (realpath(filename, resolved_path) == NULL) {
        return NULL;
    }
    
    int fd = open(resolved_path, O_RDONLY | O_NOFOLLOW);
    if (fd == -1) {
        return NULL;
    }
    
    struct stat st;
    if (fstat(fd, &st) != 0) {
        close(fd);
        return NULL;
    }
    
    if (!S_ISREG(st.st_mode)) {
        close(fd);
        return NULL;
    }
    
    FILE *file = fdopen(fd, "r");
    if (file == NULL) {
        close(fd);
        return NULL;
    }
    
    return file;
}

static char *safe_fgets(char *s, int size, FILE *stream) {
    if (s == NULL || size <= 0 || stream == NULL) {
        return NULL;
    }
    if (fgets(s, size, stream) == NULL) {
        return NULL;
    }
    size_t len = strnlen(s, size);
    if (len > 0 && s[len - 1] != '\n' && !feof(stream)) {
        int c;
        while ((c = fgetc(stream)) != '\n' && c != EOF) {
        }
        if (c == EOF) {
            clearerr(stream);
        }
    }
    return s;
}

static void process_dictionary(const char *filename) {
    if (filename == NULL) {
        fprintf(stderr, "Invalid filename\n");
        exit(EXIT_FAILURE);
    }

    if (!is_safe_path(filename)) {
        fprintf(stderr, "Unsafe or invalid filename\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (setvbuf(file, NULL, _IONBF, 0) != 0) {
        fclose(file);
        fprintf(stderr, "Failed to set buffer\n");
        exit(EXIT_FAILURE);
    }

    WordCountArray arr;
    init_array(&arr);

    char *buffer = (char *)malloc(MAX_WORD_LEN + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int ch;
    size_t pos = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (pos < MAX_WORD_LEN) {
            if (isalpha((unsigned char)ch) || ch == '\'' || ch == '-') {
                buffer[pos++] = (char)tolower((unsigned char)ch);
            } else {
                if (pos > 0) {
                    buffer[pos] = '\0';
                    add_word(&arr, buffer);
                    pos = 0;
                }
            }
        } else {
            while ((ch = fgetc(file)) != EOF && (isalpha((unsigned char)ch) || ch == '\'' || ch == '-')) {
            }
            pos = 0;
            if (ch == EOF) break;
        }
    }

    if (ferror(file)) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        clearerr(file);
    }

    if (pos > 0 && pos < MAX_WORD_LEN) {
        buffer[pos] = '\0';
        add_word(&arr, buffer);
    }

    free(buffer);
    fclose(file);
    print_top_words(&arr, TOP_N);
    free_array(&arr);
}

int main(const int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dictionary_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    process_dictionary(argv[1]);
    return EXIT_SUCCESS;
}