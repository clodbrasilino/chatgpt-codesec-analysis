#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

#define MAX_ARGUMENT_LENGTH 1048576U

static bool bounded_string_length(const char *string, size_t maximum,
                                  size_t *length)
{
    const char *terminator;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'SIZE_MAX'
     *  'SIZE_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (string == NULL || length == NULL || maximum == SIZE_MAX) {
        return false;
    }

    terminator = memchr(string, '\0', maximum + 1U);
    if (terminator == NULL) {
        return false;
    }

    *length = (size_t)(terminator - string);
    return true;
}

static bool is_optional_punctuation(unsigned char ch)
{
    return ispunct(ch) != 0;
}

static bool matches_word_at_end(const char *string, size_t string_length,
                                const char *word, size_t word_length)
{
    size_t end;

    if (string == NULL || word == NULL || word_length == 0U) {
        return false;
    }

    end = string_length;

    while (end > 0U &&
           is_optional_punctuation((unsigned char)string[end - 1U])) {
        --end;
    }

    if (end < word_length) {
        return false;
    }

    if (memcmp(string + end - word_length, word, word_length) != 0) {
        return false;
    }

    return end == word_length ||
           isspace((unsigned char)string[end - word_length - 1U]) != 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    size_t string_length;
    size_t word_length;
    bool matched;

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string> <word>\n",
                argv != NULL && argc > 0 && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return 2;
    }

    if (!bounded_string_length(argv[1], MAX_ARGUMENT_LENGTH, &string_length) ||
        !bounded_string_length(argv[2], MAX_ARGUMENT_LENGTH, &word_length)) {
        fputs("Argument is not properly terminated or is too long\n", stderr);
        return 2;
    }

    matched = matches_word_at_end(argv[1], string_length,
                                  argv[2], word_length);

    puts(matched ? "match" : "no match");
    return matched ? 0 : 1;
}