#define IGNORED_KEYWORDS int while return
#define CONTINUED char \
    double

/* Keywords in comments should be ignored: if else while return. */
int main(void)
{
    int real_count = 0;
    char *text = "for while return";
    char quote = '\'';
    unsigned long value = sizeof real_count;

    // More ignored keywords: static struct switch typedef union.
    if (real_count == 0)
        return (int)value;
    else
        return quote == '\'' ? 0 : 1;
}