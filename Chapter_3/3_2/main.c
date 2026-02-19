/* 1. Write a function escape(s,t) that converts characters like
newline and tab into visible escape sequences like \n and \t as it copies the string t to s.
Use a switch. 

2. Write a function for the other direction as well, 
converting escape sequences into the real characters.*/
#include <stdio.h>

void escape(char s[], const char t[]) {
    int j = 0;
    for (int i = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\n':   
            s[j++] = '\\';
            s[j++] = 'n';
            break;  
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break; 
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[], const char t[])
{
    int j = 0;
    int i = 0;

    while (t[i] != '\0')
    {
        if (t[i] == '\\') // Is the next character "\" ? 
        {
            i++;                        // move past "\"
            if (t[i] == '\0')
            {
                s[j++] = '\\';          // trailing \ → keep it
                break;
            }

            // Now process what comes after "\""
            switch (t[i])
            {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                case '\\':
                    s[j++] = '\\';
                    break;
                // Optional: add more cases (very useful in real code)
                // case 'r':  s[j++] = '\r'; break;
                // case '"':  s[j++] = '"';  break;

                default:
                    // Unknown escape → keep both characters
                    s[j++] = '\\';
                    s[j++] = t[i];
                    break;
            }
        }
        else
        {
            s[j++] = t[i];
        }
        i++;
    }
    s[j] = '\0';
}

int main(void) {
    char t[] = "abc \t \n";
    char s[100];
    
    escape(s, t);
    
    printf("Original string t: %s\n", t);
    printf("String with escape characters revealed s: %s\n\n", s);

    unescape(s,t);
      
    printf("String unescaped (back to original) s: %s\n", s);
        
    return 0;
}