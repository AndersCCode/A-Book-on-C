/* Write a function strindex(s,t), which returns the position of the rightmost occurence of t in s,
or -1 if there is none. */

#include <stdio.h>
#define MAXLINE 1000    /* maximum input line length */

char pattern[] = "esla";    /* pattern to search for */

/* Previous version that modifies a global variable (not recommended). 
It's just here to show the difference. The for loop is also more complex than the while based in getline_ch4.
The main advantage of getline_ch4 is that it uses the parameterized form, which makes it easer to make general use of it.*/
int getline_ch1(void)
{
    int c, i;
    //extern char line[];

    for (i = 0; i < MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        //line[i] = c;
    if (c == '\n') {
        //line[i] = c;
        ++i;
    }
    //line[i] = '\0';
    return i;
}


/* getline:  get line into s, return length */
int getline_ch4(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    // Removed to not add \n
    //if (c == '\n')
    //    s[i++] = c;
    s[i] = '\0';
    return i;
}

/* strindex:  return index of t in s, −1 if none */
int strindex(char s[], char t[])
{
    int i; // outer loop counter for s
    int j; // walks through s
    int k; // walks through t

    for (i = 0; s[i] != '\0'; i++) { // Try starting every at every position in s
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++) // Search every character of t for a match in s
            ;
        if (k > 0 && t[k] == '\0') // if commplete string is found, return start position
            return i;
    }
    return -1; // not found
}

/* find all lines matching pattern */
int main(void)
{
    char line[MAXLINE]; 
    int found = 0;

    while (getline_ch4(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0) {
            printf("Found \"%s\" in \"%s\"\n", pattern, line);
            found++;
            printf("Found = %d\n", found);
        }
        else {
            printf("Pattern \"%s\" not found in \"%s\"\n", pattern, line);
            printf("Found = %d\n", found);
        }
    return found;
}

