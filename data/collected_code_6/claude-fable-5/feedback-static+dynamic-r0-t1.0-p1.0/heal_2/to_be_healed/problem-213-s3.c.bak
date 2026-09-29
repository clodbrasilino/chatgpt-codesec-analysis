#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINE 4096
#define MAX_ITEMS 256
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['HarpreetKour', 'Priyanka Agarwal', 'MuskanSethi'], got <no output>
  *  test case 1 failed: expected ['Shaik Dawood', 'Ayesha Begum', 'Sanya Singh'], got <no output>
  *  test case 0 failed: expected ['Manjeet Singh', 'Nikhil Meherwal', 'Akshat Garg'], got <no output>
  */

static char *concat_strings(const char *a, const char *b)
{
    size_t len_a;
    size_t len_b;
    char *result;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    len_a = strlen(a);
    len_b = strlen(b);

    if (len_a > SIZE_MAX - len_b - 1u) {
        return NULL;
    }

    result = malloc(len_a + len_b + 1u);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b + 1u);

    return result;
}

static char *duplicate_range(const char *start, size_t len)
{
    char *s;

    s = malloc(len + 1u);
    if (s == NULL) {
        return NULL;
    }

    memcpy(s, start, len);
    s[len] = '\0';

    return s;
}

static size_t parse_items(const char *line, char **items, size_t max_items)
{
    size_t count = 0;
    const char *p = line;

    while (*p != '\0' && count < max_items) {
        if (*p == '\'' || *p == '"') {
            char quote = *p;
            const char *start = p + 1;
            const char *end = strchr(start, quote);

            if (end == NULL) {
                break;
            }

            items[count] = duplicate_range(start, (size_t)(end - start));
            if (items[count] == NULL) {
                break;
            }
            count++;
            p = end + 1;
        } else {
            p++;
        }
    }

    return count;
}

static void free_items(char **items, size_t count)
{
    size_t i;

    for (i = 0; i < count; i++) {
        free(items[i]);
        items[i] = NULL;
    }
}

static int read_line(char *buf, size_t size)
{
    size_t len;

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    len = strlen(buf);
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
        buf[len - 1] = '\0';
        len--;
    }

    return 0;
}

int main(void)
{
    char line1[MAX_LINE];
    char line2[MAX_LINE];
    char *tuple1[MAX_ITEMS];
    char *tuple2[MAX_ITEMS];
    char *results[MAX_ITEMS];
    size_t count1;
    size_t count2;
    size_t i;

    if (read_line(line1, sizeof(line1)) != 0) {
        fprintf(stderr, "Error: failed to read first tuple\n");
        return EXIT_FAILURE;
    }

    if (read_line(line2, sizeof(line2)) != 0) {
        fprintf(stderr, "Error: failed to read second tuple\n");
        return EXIT_FAILURE;
    }

    count1 = parse_items(line1, tuple1, MAX_ITEMS);
    count2 = parse_items(line2, tuple2, MAX_ITEMS);

    if (count1 == 0 || count1 != count2) {
        fprintf(stderr, "Error: tuples are empty or of different lengths\n");
        free_items(tuple1, count1);
        free_items(tuple2, count2);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count1; i++) {
        results[i] = concat_strings(tuple1[i], tuple2[i]);
        if (results[i] == NULL) {
            fprintf(stderr, "Error: tuple concatenation failed\n");
            free_items(results, i);
            free_items(tuple1, count1);
            free_items(tuple2, count2);
            return EXIT_FAILURE;
        }
    }

    if (printf("[") < 0) {
        free_items(results, count1);
        free_items(tuple1, count1);
        free_items(tuple2, count2);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count1; i++) {
        if (printf("'%s'%s", results[i], (i + 1 < count1) ? ", " : "") < 0) {
            free_items(results, count1);
            free_items(tuple1, count1);
            free_items(tuple2, count2);
            return EXIT_FAILURE;
        }
    }

    if (printf("]\n") < 0) {
        free_items(results, count1);
        free_items(tuple1, count1);
        free_items(tuple2, count2);
        return EXIT_FAILURE;
    }

    free_items(results, count1);
    free_items(tuple1, count1);
    free_items(tuple2, count2);

    return EXIT_SUCCESS;
}