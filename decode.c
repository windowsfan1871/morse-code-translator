#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	const char* morse;
	char c;
} morse_code_char_t;

morse_code_char_t morse_code_char_arr[] = {
	{".-", 'A'}, 
	{"-...", 'B'}, 
	{"-.-.", 'C'}, 
	{"-..", 'D'}, 
	{".", 'E'}, 
	{"..-.", 'F'}, 
	{"--.", 'G'}, 
	{"....", 'H'}, 
	{"..", 'I'}, 
	{".---", 'J'}, 
	{"-.-", 'K'}, 
	{".-..", 'L'}, 
	{"--", 'M'}, 
	{"-.", 'N'}, 
	{"---", 'O'}, 
	{".--.", 'P'}, 
	{"--.-", 'Q'}, 
	{".-.", 'R'}, 
	{"...", 'S'}, 
	{"-", 'T'}, 
	{"..-", 'U'}, 
	{"...-", 'V'}, 
	{".--", 'W'}, 
	{"-..-", 'X'}, 
	{"-.--", 'Y'}, 
	{"--..", 'Z'}, 
	{"-----", '0'}, 
	{".----", '1'}, 
	{"..---", '2'}, 
	{"...--", '3'}, 
	{"....-", '4'}, 
	{".....", '5'}, 
	{"-....", '6'}, 
	{"--...", '7'}, 
	{"---..", '8'}, 
	{"----.", '9'}, 
	{"-.-.-.", ';'}, 
	{"---...", ':'}, 
	{"..--..", '?'}, 
	{"-.-.--", '!'}, 
	{".-.-.", '+'}, 
	{"-....-", '-'}, 
	{"-...-", '='}, 
	{"--..--", ','}, 
	{".-.-.-", '.'}, 
	{".----.", '\''}, 
	{".-..-.", '"'}, 
	{"/", ' '},
	{"-.--.", '('},
	{"-.--.-", ')'},
	{"..--.-", '_'},
	{"-..-.", '/'},
};

const int morse_code_char_count = sizeof(morse_code_char_arr) / sizeof(morse_code_char_arr[0]);

char morse_to_char(const char* morse) {

	for(int i = 0; i < morse_code_char_count; i++) {
		if(!strcmp(morse, morse_code_char_arr[i].morse)) {
			return morse_code_char_arr[i].c;
		}
	}

	return '?';
}

int morse_to_str(const char* input_filename, const char* output_filename) {
	FILE* input = fopen(input_filename, "r");
	if(!input)
		return -1;

	FILE* output = fopen(output_filename, "w");
	if(!output) {
		fclose(input);
		return -2;
	}

	fseek(input, 0, SEEK_END);
	long filesize = ftell(input);
	fseek(input, 0, SEEK_SET);
	char* buffer = malloc(filesize);
	if(!buffer) {
		fclose(input);
		fclose(output);
		return -1;
	}

	memset(buffer, 0, filesize);

	fread(buffer, filesize - 1, 1, input);

	char* saveptr;
	char* token = strtok_r(buffer, " ", &saveptr);

	while(token != NULL) {
		char c = morse_to_char(token);

		fprintf(output, "%c", c);

		token = strtok_r(NULL, " ", &saveptr);
	}

	free(buffer);
	fclose(input);
	fclose(output);
	return 0;
}

int main(int argc, char** argv) {
	if(argc < 3) { 
		printf("Usage: %s <input morse code file> <output text file>\n", argv[0]);
		return -1;
	}

	return morse_to_str(argv[1], argv[2]);
}
