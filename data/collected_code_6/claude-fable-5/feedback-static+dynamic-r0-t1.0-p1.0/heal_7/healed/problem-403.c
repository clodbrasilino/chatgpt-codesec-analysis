#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_MAX_LEN 4096

static int is_valid_host(const char *s, size_t len)
{
    size_t i;
    size_t label_len = 0;

    if (s == NULL || len == 0 || len > 253) {
        return 0;
    }
    if (!isalnum((unsigned char)s[0])) {
        return 0;
    }
    if (!isalnum((unsigned char)s[len - 1])) {
        return 0;
    }
    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)s[i];
        if (c == '.') {
            if (label_len == 0) {
                return 0;
            }
            if (i > 0 && s[i - 1] == '-') {
                return 0;
            }
            if (i + 1 < len && s[i + 1] == '-') {
                return 0;
            }
            label_len = 0;
        } else if (isalnum(c) || c == '-') {
            label_len++;
            if (label_len > 63) {
                return 0;
            }
        } else {
            return 0;
        }
    }
    return 1;
}

static int is_valid_port(const char *s, size_t len)
{
    size_t i;
    long value = 0;

    if (s == NULL || len < 1 || len > 5) {
        return 0;
    }
    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
        value = value * 10 + (s[i] - '0');
    }
    if (value < 1 || value > 65535) {
        return 0;
    }
    return 1;
}

static int is_valid_path(const char *s)
{
    const char *allowed = "._~%/?#=&+-";
    size_t i;

    if (s == NULL || s[0] != '/') {
        return 0;
    }
    for (i = 1; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];
        if (!isalnum(c) && strchr(allowed, (int)c) == NULL) {
            return 0;
        }
    }
    return 1;
}

int is_valid_url(const char *url)
{
    const char *rest;
    const char *host_start;
    const char *p;
    const char *host_end;
    const char *port_start;
    const char *port_end;

    if (url == NULL) {
        return 0;
    }

    if (strncmp(url, "https://", 8) == 0) {
        rest = url + 8;
    } else if (strncmp(url, "http://", 7) == 0) {
        rest = url + 7;
    } else if (strncmp(url, "ftp://", 6) == 0) {
        rest = url + 6;
    } else {
        return 0;
    }

    host_start = rest;
    p = rest;
    while (*p != '\0' && *p != ':' && *p != '/') {
        p++;
    }
    host_end = p;

    if (!is_valid_host(host_start, (size_t)(host_end - host_start))) {
        return 0;
    }

    if (*p == ':') {
        port_start = p + 1;
        port_end = port_start;
        while (*port_end != '\0' && *port_end != '/') {
            port_end++;
        }
        if (!is_valid_port(port_start, (size_t)(port_end - port_start))) {
            return 0;
        }
        p = port_end;
    }

    if (*p == '\0') {
        return 1;
    }

    if (!is_valid_path(p)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    char *line;

    line = calloc(LINE_MAX_LEN, sizeof(char));
    if (line == NULL) {
        return EXIT_FAILURE;
    }

    while (fgets(line, LINE_MAX_LEN, stdin) != NULL) {
        size_t len;

        line[LINE_MAX_LEN - 1] = '\0';
        len = strnlen(line, LINE_MAX_LEN);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            len--;
        }
        if (is_valid_url(line) == 1) {
            printf("True\n");
        } else {
            printf("False\n");
        }
        fflush(stdout);
        memset(line, 0, LINE_MAX_LEN);
    }

    free(line);
    return EXIT_SUCCESS;
}