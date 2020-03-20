#include <stdio.h>
#include <ctype.h>
#include <string.h>

char line[256];

int main() {
	for (;;) {
		// read a line
		char * s = fgets(line, 256, stdin);
		if (!s) {
			break;
		}
		
		// replace newline with a terminator
		char * nl = strchr(line, '\n');
		if (nl) {
			*nl = '\0';
		}
		
		// convert to upper case
		for ( ; *s; ++s) {
			*s = toupper(*s);
		}
		
		// output
		puts(line);
	}
}
