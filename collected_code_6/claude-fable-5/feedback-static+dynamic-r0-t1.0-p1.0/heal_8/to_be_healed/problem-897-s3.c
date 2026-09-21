#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEN 1024

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t i = 0U;

    if (s == NULL) {
        return 0U;
    }
    while (i < max_len && s[i] != '\0') {
        i++;
    }
    return i;
}

int is_word_present(const char *sentence, const char *word)
{
    size_t word_len;
    const char *p;
    const char *end;

    if (sentence == NULL || word == NULL) {
        return 0;
    }

    word_len = bounded_strlen(word, MAX_LEN);
    if (word_len == 0U || word_len >= MAX_LEN) {
        return 0;
    }

    p = sentence;
    end = sentence + bounded_strlen(sentence, MAX_LEN);

    while (p < end && *p != '\0') {
        while (p < end && *p != '\0' && !isalnum((unsigned char)*p)) {
            p++;
        }
        if (p >= end || *p == '\0') {
            break;
        }
        const char *start = p;
        while (p < end && *p != '\0' && isalnum((unsigned char)*p)) {
            p++;
        }
        size_t token_len = (size_t)(p - start);
        if (token_len == word_len && strncmp(start, word, word_len) == 0) {
            return 1;
        }
    }
    return 0;
}

static void strip_newline(char *s, size_t max_len)
{
    size_t len;

    if (s == NULL || max_len == 0U) {
        return;
    }
    len = bounded_strlen(s, max_len);
    while (len > 0U && (s[len - 1U] == '\n' || s[len - 1U] == '\r')) {
        s[len - 1U] = '\0';
        len--;
    }
}

static int read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size == 0U || size > (size_t)INT_MAX) {
        return 0;
    }
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return 0;
    }
    buffer[size - 1U] = '\0';
    strip_newline(buffer, size);
    return 1;
}

static void print_result(int present)
{
    if (present == 1) {
        fputs("True\n", stdout);
    } else {
        fputs("False\n", stdout);
    }
    fflush(stdout);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[MAX_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_LEN];
    int sentence_ok;
    int word_ok;

    memset(sentence, 0, sizeof(sentence));
    memset(word, 0, sizeof(word));

    sentence_ok = read_line(sentence, sizeof(sentence));
    word_ok = read_line(word, sizeof(word));

    if (sentence_ok == 0 || word_ok == 0) {
        print_result(0);
        return EXIT_SUCCESS;
    }

    print_result(is_word_present(sentence, word));

    return EXIT_SUCCESS;
}