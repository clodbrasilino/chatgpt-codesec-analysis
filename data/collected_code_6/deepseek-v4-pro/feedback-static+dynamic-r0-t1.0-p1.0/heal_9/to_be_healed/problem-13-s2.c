#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_WORD_LEN 128
#define INITIAL_CAPACITY 128
#define MAX_LINE_LEN (MAX_WORD_LEN * 1024)

typedef struct {
    char *word;
    int count;
} WordEntry;

typedef struct {
    WordEntry *entries;
    size_t size;
    size_t capacity;
} WordTable;

static void init_table(WordTable *table) {
    table->capacity = INITIAL_CAPACITY;
    table->size = 0;
    table->entries = malloc(table->capacity * sizeof(WordEntry));
    if (!table->entries) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

static void free_table(WordTable *table) {
    if (table->entries) {
        for (size_t i = 0; i < table->size; i++) {
            free(table->entries[i].word);
        }
        free(table->entries);
        table->entries = NULL;
    }
    table->size = 0;
    table->capacity = 0;
}

static char *duplicate_word(const char *word) {
    size_t len = strnlen(word, MAX_WORD_LEN);
    char *copy = malloc(len + 1);
    if (!copy) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, word, len);
    copy[len] = '\0';
    return copy;
}

static int find_word(const WordTable *table, const char *word) {
    for (size_t i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].word, word) == 0) {
            return (int)i;
        }
    }
    return -1;
}

static void add_word(WordTable *table, const char *word) {
    int index = find_word(table, word);
    if (index >= 0) {
        table->entries[index].count++;
        return;
    }

    if (table->size == table->capacity) {
        if (table->capacity > SIZE_MAX / 2 / sizeof(WordEntry)) {
            fprintf(stderr, "Table capacity overflow\n");
            exit(EXIT_FAILURE);
        }
        size_t new_capacity = table->capacity * 2;
        WordEntry *new_entries = realloc(table->entries, new_capacity * sizeof(WordEntry));
        if (!new_entries) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        table->entries = new_entries;
        table->capacity = new_capacity;
    }

    table->entries[table->size].word = duplicate_word(word);
    table->entries[table->size].count = 1;
    table->size++;
}

static void normalize_word(char *word) {
    size_t len = strnlen(word, MAX_WORD_LEN);
    while (len > 0 && (ispunct((unsigned char)word[len - 1]) ||
                       isspace((unsigned char)word[len - 1]))) {
        word[len - 1] = '\0';
        len--;
    }
}

static void process_text(WordTable *table, const char *text) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN];
    size_t pos = 0;
    size_t i = 0;

    while (text[i] != '\0') {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'') {
            if (pos < MAX_WORD_LEN - 1) {
                buffer[pos++] = tolower((unsigned char)text[i]);
            }
        } else if (pos > 0) {
            buffer[pos] = '\0';
            normalize_word(buffer);
            if (buffer[0] != '\0') {
                add_word(table, buffer);
            }
            pos = 0;
        }
        i++;
    }

    if (pos > 0) {
        buffer[pos] = '\0';
        normalize_word(buffer);
        if (buffer[0] != '\0') {
            add_word(table, buffer);
        }
    }
}

static int compare_entries(const void *a, const void *b) {
    const WordEntry *entry_a = (const WordEntry *)a;
    const WordEntry *entry_b = (const WordEntry *)b;
    if (entry_b->count != entry_a->count) {
        return entry_b->count - entry_a->count;
    }
    return strcmp(entry_a->word, entry_b->word);
}

static void print_most_common(const WordTable *table, int top_n) {
    size_t count = table->size < (size_t)top_n ? table->size : (size_t)top_n;
    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", table->entries[i].word, table->entries[i].count);
    }
}

static int is_special_path(const char *path) {
    if (strncmp(path, "/dev/", 5) == 0 ||
        strncmp(path, "/proc/", 6) == 0 ||
        strncmp(path, "/sys/", 5) == 0) {
        return 1;
    }
    return 0;
}

static int verify_regular_file(const char *path) {
    struct stat path_stat;
    if (lstat(path, &path_stat) != 0) {
        return 0;
    }
    if (S_ISLNK(path_stat.st_mode)) {
        return 0;
    }
    if (!S_ISREG(path_stat.st_mode)) {
        return 0;
    }
    if (stat(path, &path_stat) != 0) {
        return 0;
    }
    if (!S_ISREG(path_stat.st_mode)) {
        return 0;
    }
    return 1;
}

static int read_line_safely(FILE *file, char *buffer, size_t size) {
    if (!fgets(buffer, (int)size, file)) {
        return 0;
    }
    size_t len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 1;
    }
    if (len >= size - 1 && buffer[size - 2] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = fgetc(file)) != '\n' && c != EOF) {
        }
    }
    return 1;
}

void count_most_common_words(const char *filename, int top_n) {
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    int fd = open(filename, O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd < 0) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return;
    }

    struct stat fd_stat;
    if (fstat(fd, &fd_stat) != 0 || !S_ISREG(fd_stat.st_mode)) {
        fprintf(stderr, "Not a regular file: %s\n", filename);
        close(fd);
        return;
    }

    FILE *file = fdopen(fd, "r");
    if (!file) {
        fprintf(stderr, "Cannot associate stream with file: %s\n", filename);
        close(fd);
        return;
    }

    WordTable table;
    init_table(&table);

    char *line_buffer = malloc(MAX_LINE_LEN);
    if (!line_buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        free_table(&table);
        exit(EXIT_FAILURE);
    }

    while (read_line_safely(file, line_buffer, MAX_LINE_LEN)) {
        process_text(&table, line_buffer);
    }

    if (ferror(file)) {
        fprintf(stderr, "Error reading file: %s\n", filename);
    }

    fclose(file);
    free(line_buffer);

    qsort(table.entries, table.size, sizeof(WordEntry), compare_entries);

    print_most_common(&table, top_n);

    free_table(&table);
}

static int resolve_path_safely(const char *input, char *resolved, size_t resolved_size) {
    if (!input || !resolved || resolved_size == 0) {
        return 0;
    }
    if (strnlen(input, PATH_MAX) >= PATH_MAX) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder realpath: This function does not protect against buffer overflows, and some implementations can overflow internally (CWE-120/CWE-785!). Ensure that the destination buffer is at least of size MAXPATHLEN, andto protect against implementation problems, the input argument should also be checked to ensure it is no larger than MAXPATHLEN. (risk 3, buffer)
     */
    if (!realpath(input, resolved)) {
        return 0;
    }
    if (strnlen(resolved, resolved_size) >= resolved_size) {
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [top_n]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int top_n = 10;

    if (argc >= 3) {
        char *endptr;
        errno = 0;
        long value = strtol(argv[2], &endptr, 10);
        if (errno == 0 && *endptr == '\0' && value > 0 && value <= 1000) {
            top_n = (int)value;
        } else {
            fprintf(stderr, "Invalid top_n value, using default 10\n");
        }
    }

    if (is_special_path(filename)) {
        fprintf(stderr, "Refusing to open special path: %s\n", filename);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char resolved_path[PATH_MAX];
    if (!resolve_path_safely(filename, resolved_path, sizeof(resolved_path))) {
        fprintf(stderr, "Cannot resolve file path: %s\n", filename);
        return EXIT_FAILURE;
    }

    if (is_special_path(resolved_path)) {
        fprintf(stderr, "Refusing to open special file: %s\n", resolved_path);
        return EXIT_FAILURE;
    }

    if (!verify_regular_file(resolved_path)) {
        fprintf(stderr, "Not a regular file or symlink not allowed: %s\n", resolved_path);
        return EXIT_FAILURE;
    }

    count_most_common_words(resolved_path, top_n);

    return EXIT_SUCCESS;
}