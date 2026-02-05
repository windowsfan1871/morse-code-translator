#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char* morse_code[] = {
	/* A */
	".- ",
	/* B */
	"-... ",
	/* C */
	"-.-. ",
	/* D */
	"-.. ",
	/* E */
	". ",
	/* F */
	"..-. ",
	/* G */
	"--. ",
	/* H */
	".... ",
	/* I */
	".. ",
	/* J */
	".--- ",
	/* K */
	"-.- ",
	/* L */
	".-.. ",
	/* M */
	"-- ",
	/* N */
	"-. ",
	/* O */
	"--- ",
	/* P */
	".--. ",
	/* Q */
	"--.- ",
	/* R */
	".-. ",
	/* S */
	"... ",
	/* T */
	"- ",
	/* U */
	"..- ",
	/* V */
	"...- ",
	/* W */
	".-- ",
	/* X */
	"-..- ",
	/* Y */
	"-.-- ",
	/* Z */
	"--.. ",
	/* space */
	"/ ",
	/* 0 */
	"----- ",
	/* 1 */
	".---- ",
	/* 2 */
	"..--- ",
	/* 3 */
	"...-- ",
	/* 4 */
	"....- ",
	/* 5 */
	"..... ",
	/* 6 */
	"-.... ",
	/* 7 */
	"--... ",
	/* 8 */
	"---.. ",
	/* 9 */
	"----. ",
	/* ? */
	"..--.. ",
	/* ! */
	"-.-.-- ",
	/* . */
	".-.-.- ",
	/* , */
	"--..-- ",
	/* ; */
	"-.-.-. ",
	/* : */
	"---... ",
	/* + */
	".-.-. ",
	/* - */
	"-....- ",
	/* / */
	"-..-.",
	/* = */
	"-...-",
};

const char* char_to_morse(char c) {
	if(c >= 'A' && c <= 'Z')
		return morse_code[c - 'A'];

	else if(c == ' ')
		return morse_code[26];

	else if(c >= '0' && c <= '9')
		return morse_code[27 + (c - '0')];

	else if(c == '?')
		return morse_code[37];

	else if(c == '!')
		return morse_code[38];

	else if(c == '.')
		return morse_code[39];

	else if(c == ',')
		return morse_code[40];

	else if(c == ';')
		return morse_code[41];

	else if(c == ':')
		return morse_code[42];
	
	else if(c == '+')
		return morse_code[43];

	else if(c == '-')
		return morse_code[44];

	else if(c == '/')
		return morse_code[45];

	else if(c == '=')
		return morse_code[46];
	else
		return "";
}

int convert_to_morse(const char* input_filename, const char* output_filename) {
	FILE* input = fopen(input_filename, "r");
	if(!input) return -1;
	FILE* output = fopen(output_filename, "w+");
	if(!output) {
		fclose(input);
		return -2;
	}

	fseek(input, 0, SEEK_END);
	long input_size = ftell(input);
	fseek(input, 0, SEEK_SET);

	char* buffer = malloc(input_size);
	if(!buffer) {
		fclose(input);
		fclose(output);
		return -3;
	}
	memset(buffer, 0, input_size);

	fread(buffer, input_size, 1, input);

	for(int i = 0; i < strlen(buffer); i++) {
		char c = toupper(buffer[i]);
		const char* morse = char_to_morse(c);

		if(strlen(morse) > 0) {
			fprintf(output, "%s", morse);
		}
	}

	free(buffer);
	fclose(input);
	fclose(output);

	return 0;
}

int main(int argc, char** argv) {

	if(argc < 3) {
		printf("Syntax: %s <input text file> <output morse code file>\n", argv[0]);
		return -1;
	}

	convert_to_morse(argv[1], argv[2]);

	return 0;
}
