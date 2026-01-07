#include <stdio.h>
#include <termios.h> // Control terminal settings
#include <unistd.h> // STDIN_FILENO and TCSANOW (apply immediately)

// Takes a byte c and determines how many bytes make up a single UTF-8 character.
// First use mask to find the relevant bits. Then compare to the result.

static int utf8_char_len(unsigned char c) {
    if (c < 0x80) return 1; // Is ASCII?
    if ((c & 0xe0) == 0xc0) return 2; // Mask=0xe0 1110 0000 (only 3 first bits are relevant), result=1100 0000 
    if ((c & 0xf0) == 0xe0) return 3; // Mask=0xf0 1111 0000 (only 4 first bits are relevant), result=1110 0000
    if ((c & 0xf8) == 0xf0) return 4; // Mask=0xe0 1111 1000 (only 5 first bits are relevant), result=1111 0000
    return 1;
}

int main() {
    struct termios oldt, newt; // struct to hold settings
    tcgetattr(STDIN_FILENO, &oldt); // Get the current settings and store them in oldt.
    newt = oldt; // Copy old settings to new.
    newt.c_lflag &= ~(ICANON | ECHO); // Turn off "canonical" and echoing. This makes input arrive character-by-character instantly.
    newt.c_cc[VMIN] = 1; // Wait for at least 1 character before getchar() returns.
    newt.c_cc[VTIME] = 0; // No timeout-return as soon as a character is available.
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply the new settings immediately.

    printf("=== Real-time word length histogram ===\n");
    printf("Type text - space/tab/enter ends word - Ctrl-D quits\n\n");

    int c;
    int len = 0;

    while ((c = getchar()) != EOF) {
        if (c == 4) { break; }   // Handle Ctrl-D explicitly

        if (c == ' ' || c == '\t' || c == '\n') { // space, tab or newline (enter)
            if (len > 0) {
                printf("[%2d] ", len);
                for (int i = 0; i < len; i++) putchar('*');
                putchar('\n');
                len = 0; // reset length for next word
            }
        }
        else if ((c & 0x80) == 0) { // An ASCII-character is entered
            len++;
        }
        else { // Bytes 2 to 4 (continuation bytes) starts with 10xxxxxx (according to UTF-8 standard)
            int bytes = utf8_char_len((unsigned char)c); // How many bytes (2-4)?
            len++;
            // printf("Bytes: %d\n", bytes); // Debug - confirms 2 bytes or more
            for (int i = 1; i < bytes && (c = getchar()) != EOF; i++) { 
                if ((c & 0xc0) != 0x80) { // If true it's a new start byte, not a proper continuation byte.
                    ungetc(c, stdin); // push it back - next loop will treat it as a new char
                    break; // word ended on invalid sequence
                }
            }
        }
    }

    if (len > 0) { // If Ctrl-D is pressed mid-word
        printf("\n[%2d] ", len);
        for (int i = 0; i < len; i++) putchar('*');
        putchar('\n');
    }

    printf("\nBye!\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore the original terminal settings
    return 0;
}