#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_valid_host(const char *s, size_t len)
{
    size_t i;

    if (len == 0) {
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
        if (!isalnum(c) && c != '.' && c != '-') {
            return 0;
        }
    }
    return 1;
}

static int is_valid_port(const char *s, size_t len)
{
    size_t i;

    if (len < 1 || len > 5) {
        return 0;
    }
    for (i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}

static int is_valid_path(const char *s)
{
    const char *allowed = "._~%/?#=&+-";
    size_t i;

    if (s[0] != '/') {
        return 0;
    }
    for (i = 1; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];
        if (!isalnum(c) && strchr(allowed, c) == NULL) {
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
    const char *test_urls[] = {
        "https://www.example.com",
        "http://example.com/path/to/page?name=value",
        "ftp://files.example.org",
        "https://example.com:8080/index.html",
        "not_a_url",
        "http://",
        "https://sub.domain.example.com/page#section"
    };
    size_t count = sizeof(test_urls) / sizeof(test_urls[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = is_valid_url(test_urls[i]);
        if (result == 1) {
            printf("True\n");
        } else {
            printf("False\n");
        }
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}