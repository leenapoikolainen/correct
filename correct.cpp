#include <iostream>

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

/* converts a binary string representation into a character */
char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */

void text_to_binary(const char *text, char *binary) { 
  if (*text == '\0')
    return;
  
  else {
    char stored_binary[9];
    ascii_to_binary(*text, stored_binary);
    strcpy(binary, stored_binary);
    text_to_binary(text + 1, binary + 8);
  }
}


void binary_to_text(const char *binary, char *text){
  if (*binary == '\0'){
    *text = '\0';
    return;
  }
  
  else {
    char ch;
    char stored_binary[9];
    for (int i = 0; i < 8; i++) {
      stored_binary[i] = binary[i];
    }
    stored_binary[8] = '\0';
    ch = binary_to_ascii(stored_binary);
    *text = ch;
    binary_to_text(binary + 8, text + 1);
  }
}

int parity(int n1, int n2, int n3) {
  if ((n1 + n2 + n3) % 2 == 0)
    return 0;
  else
    return 1;
}
int parity(int n1, int n2, int n3, int n4){
  if ((n1 + n2 + n3 + n4) % 2 == 0)
    return 0;
  else
    return 1;
}

void store_code_from_position(const char *data, int position, char *code){
  for (int i = position; i < position + 4; i++) {
    *code++ = data[i];
  }
  *code = '\0';
}

void store_binary_from_position(const char *data, int position, char *binary){
  for (int i = position; i < position + 7; i++) {
    *binary++ = data[i];
  }
  *binary = '\0';
}

void add_error_correction(const char *data, char *correct){
  int length = strlen(data);
  for (int i = 0; i < length; i = i + 4) {
    char code[5];
    store_code_from_position(data, i, code);
    int d1 = code[0] -'0';
    int d2 = code[1] -'0';
    int d3 = code[2] -'0';
    int d4 = code[3] -'0';

    int c1 = parity(d1, d2, d4);
    int c2 = parity(d1, d3, d4);
    int c3 = parity(d2, d3, d4);

    *correct++ = c1 + '0';
    *correct++ = c2 + '0';
    *correct++ = d1 + '0';
    *correct++ = c3 + '0';
    *correct++ = d2 + '0';
    *correct++ = d3 + '0';
    *correct++ = d4 + '0';
  }
  *correct = '\0';
}

int decode(const char *received, char *correct){
  int length = strlen(received);
  int errors = 0;
  for (int i = 0; i < length; i = i + 7) {
    char binary[8];
    store_binary_from_position(received, i, binary);
    int binary_int[7];
    for (int i = 0; i < 7; i++){
      binary_int[i] = binary[i] - '0';
    }
        
    int p1 = parity(binary_int[3], binary_int[4], binary_int[5], binary_int[6]);
    int p2 = parity(binary_int[1], binary_int[2], binary_int[5], binary_int[6]);
    int p3 = parity(binary_int[0], binary_int[2], binary_int[4], binary_int[6]);

    if ((p1 + p2 + p3) > 0) {
      errors++;
      int position = p1 * 4 + p2 * 2 + p3 * 1 - 1;
      if (binary_int[position] == 1)
        binary_int[position] = 0;
      else
        binary_int[position] = 1;
    }
    *correct++ = binary_int[2] + '0';
    *correct++ = binary_int[4] + '0';
    *correct++ = binary_int[5] + '0';
    *correct++ = binary_int[6] + '0';
  }
  return errors;
}


/* ITERATIVE VERSIONS

void store_binary_from_position(const char *binary_string, int position, char *binary){
  for(int i = position; i < position + 8; i++) {
    *binary = binary_string[i];
    binary++;
  }
  *binary = '\0';
}
void binary_to_text(const char *binary, char *text){
  strcpy(text, "");
  char ch;
  char stored_binary[9];
  int length = strlen(binary);
  for (int i = 0; i < length; i = i + 8) {
    store_binary_from_position(binary, i, stored_binary);
    ch = binary_to_ascii(stored_binary);
    *text++ = ch;
  }
  *text = '\0';
}

void text_to_binary(const char *text, char *binary) {
  strcpy(binary,"");
  char stored_binary[9];
  
  while (*text != '\0') {
    ascii_to_binary(*text, stored_binary);
    strcat(binary, stored_binary);
    text++;
  }
}
*/