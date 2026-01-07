#include <stdio.h>
#include <termios.h> // Control terminal settings
#include <unistd.h> // STDIN_FILENO and TCSANOW (apply immediately)

#define LOWER 32
#define UPPER 126
#define MAX_CHAR (UPPER - LOWER + 1)

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
    int count[MAX_CHAR] = {0}; // Array for frequencies

    // Read and count
    while ((c = getchar()) != EOF) {
        if (c == 4) { break; }   // Handle Ctrl-D explicitly

        if (c == ' ' || c == '\t' || c == '\n') { // space, tab or newline (enter)
            // Print histogram
            for (int i = 0; i < MAX_CHAR; i++) {
                if (count[i] > 0) {
                    printf("%c: ", (char)(i + LOWER));
                    for (int j = 0; j < count[i]; j++) {
                        putchar('*');
                    }
                    putchar('\n');
                }
            }
        }
        else if (c >= LOWER && c <= UPPER) { // Printable ASCII range
            count[c - LOWER]++;
        }    
    }
tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore the original terminal settings
return 0;
}