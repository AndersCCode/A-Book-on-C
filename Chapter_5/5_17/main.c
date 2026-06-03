/* Add a field-handling capability, so sorting may be done on fields within lines, each field sorted
according to an independent set of options. (The index for this book was sorted with -df for the index category 
and -n for the page numbers)

gcc -Wall -Wextra -O2 -o sort main.c

Examples:
    printf '%s\n' "Binary search  123" "binary tree 45" "Binary search  7" | ./sort -k1df -k2n
    printf '%s\n' zebra apple 42 7 banana | ./sort
    printf '%s\n' zebra apple 42 7 banana | ./sort -r
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES   5000
#define MAXLEN     1000
#define MAXSTORAGE 1000000
#define MAXKEYS    32

char *lineptr[MAXLINES];
char linebuf[MAXSTORAGE];

/* legacy whole-line flags if no -k is used */
static int g_numeric = 0;
static int g_fold = 0;
static int g_directory = 0;
static int reverse = 0;

typedef struct {
    int field;      /* 0 = whole line, 1 = first field, 2 = second, ... */
    int numeric;    /* -n */
    int fold;       /* -f */
    int directory;  /* -d */
} Key;

static Key keys[MAXKEYS];
static int nkeys = 0;

static int is_dir_char(int c)
{
    unsigned char uc = (unsigned char)c;
    return isalnum(uc) || isspace(uc);
}

/* Return start/end (end is one-past-last) of field k in line.
   Fields are whitespace-separated. field==0 means whole line. */
static void field_range(const char *line, int field, const char **start, const char **end)
{
    const char *p = line;

    if (field <= 0) {
        *start = line;
        *end = line + strlen(line);
        return;
    }

    /* skip leading blanks */
    while (*p && isspace((unsigned char)*p))
        p++;

    /* walk fields */
    for (int f = 1; f < field && *p; f++) {
        while (*p && !isspace((unsigned char)*p))
            p++;
        while (*p && isspace((unsigned char)*p))
            p++;
    }

    *start = p;
    while (*p && !isspace((unsigned char)*p))
        p++;
    *end = p;
}

/* Compare two slices [a,ae) and [b,be) lexicographically with optional -f and -d */
static int slice_textcmp(const char *a, const char *ae,
                         const char *b, const char *be,
                         int fold, int directory)
{
    for (;;) {
        int ca, cb;

        if (directory) {
            while (a < ae && !is_dir_char((unsigned char)*a))
                a++;
            while (b < be && !is_dir_char((unsigned char)*b))
                b++;
        }

        ca = (a < ae) ? (unsigned char)*a : 0;
        cb = (b < be) ? (unsigned char)*b : 0;

        if (fold) {
            ca = tolower((unsigned char)ca);
            cb = tolower((unsigned char)cb);
        }

        if (ca != cb)
            return ca - cb;

        if (ca == 0)
            return 0;

        a++;
        b++;
    }
}

/* Numeric compare two slices (copies into small buffers to NUL-terminate) */
static int slice_numcmp(const char *a, const char *ae,
                        const char *b, const char *be)
{
    char ta[MAXLEN], tb[MAXLEN];
    size_t na = (size_t)(ae - a);
    size_t nb = (size_t)(be - b);

    if (na >= sizeof ta) na = sizeof ta - 1;
    if (nb >= sizeof tb) nb = sizeof tb - 1;

    memcpy(ta, a, na); ta[na] = '\0';
    memcpy(tb, b, nb); tb[nb] = '\0';

    double va = atof(ta);
    double vb = atof(tb);

    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

static int keycmp(const char *s1, const char *s2)
{
    for (int i = 0; i < nkeys; i++) {
        const char *a, *ae, *b, *be;
        field_range(s1, keys[i].field, &a, &ae);
        field_range(s2, keys[i].field, &b, &be);

        int r;
        if (keys[i].numeric)
            r = slice_numcmp(a, ae, b, be);
        else
            r = slice_textcmp(a, ae, b, be, keys[i].fold, keys[i].directory);

        if (r != 0)
            return reverse ? -r : r;
    }
    return 0;
}

static void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

static int get_line(char *s, int lim)
{
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = (char)c;
    if (c == '\n')
        *s++ = (char)c;
    *s = '\0';
    return (int)(s - start);
}

static int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p = linebuf;
    char *end = linebuf + MAXSTORAGE;
    char line[MAXLEN];

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len + 1 > end)
            return -1;
        if (len > 0 && line[len - 1] == '\n')
            line[--len] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
        p += len + 1;
    }
    return nlines;
}

static void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

static void mysort(void *v[], int left, int right,
                   int (*comp)(const char *, const char *))
{
    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    int last = left;

    for (int i = left + 1; i <= right; i++) {
        if ((*comp)((const char *)v[i], (const char *)v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    mysort(v, left, last - 1, comp);
    mysort(v, last + 1, right, comp);
}

/* Parse -k like: -k1df, -k2n, -k3fd, etc. */
static void add_key_from_arg(const char *arg)
{
    /* arg points at the 'k' in "-k..." or at the digits in "k..." */
    if (*arg == 'k') arg++;

    int field = 0;
    while (isdigit((unsigned char)*arg)) {
        field = field * 10 + (*arg - '0');
        arg++;
    }

    if (field <= 0 || nkeys >= MAXKEYS)
        return;

    Key k = {0};
    k.field = field;

    for (; *arg; arg++) {
        if (*arg == 'n') k.numeric = 1;
        else if (*arg == 'f') k.fold = 1;
        else if (*arg == 'd') k.directory = 1;
    }

    keys[nkeys++] = k;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) reverse = 1;
        else if (strcmp(argv[i], "-n") == 0) g_numeric = 1;
        else if (strcmp(argv[i], "-f") == 0) g_fold = 1;
        else if (strcmp(argv[i], "-d") == 0) g_directory = 1;
        else if (strncmp(argv[i], "-k", 2) == 0) add_key_from_arg(argv[i] + 1);
    }

    /* If no keys specified, use one whole-line key with legacy flags */
    if (nkeys == 0) {
        keys[nkeys++] = (Key){ .field = 0, .numeric = g_numeric, .fold = g_fold, .directory = g_directory };
    }

    int nlines = readlines(lineptr, MAXLINES);
    if (nlines < 0) {
        printf("input is too big to sort\n");
        return 1;
    }

    mysort((void **)lineptr, 0, nlines - 1, keycmp);
    writelines(lineptr, nlines);
    return 0;
}