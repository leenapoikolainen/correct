#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(const char *binary);
void text_to_binary(const char *text, char *binary);
void binary_to_text(const char *binary, char *text);
void add_error_correction(const char *data, char *correct);
int parity(int n1, int n2, int n3);
int parity(int n1, int n2, int n3, int n4);
void store_code_from_position(const char *data, int position, char *code);
int decode(const char *received, char *correct);

#endif
