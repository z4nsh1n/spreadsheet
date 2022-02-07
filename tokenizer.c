#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

enum Type {
  None,
  Int,
  Float,
  String,
};

struct Token {
  enum Type type;
  char* text;
};

struct Token new_token(void) {
  struct Token t = {
    None,
    0
  };

  return t;
}

struct Tokenizer {
  size_t size;
  struct Token *tokens;
};

struct Tokenizer new_tokenizer(size_t size) {
  struct Tokenizer tokenizer = {
    size,
    malloc(sizeof(struct Token) * size),
  };

  return tokenizer;
}

struct Tokenizer tokenize(char *input) {
  struct Tokenizer tokenizer = new_tokenizer(50);
  struct Token current_token = new_token();

  int tokenizer_index = 0;
  
  char *start = input;
  char *end = start;

  while (*end != '\x0') {
    switch (*end) {
      case ' ':
      case '\t':
      case '\r':
      case '\n':
        current_token.text = strndup(start, end-start);
        tokenizer.tokens[tokenizer_index] = current_token;

        current_token = new_token();
        tokenizer_index++;
        end++;
        start = end;
        break;
      case '.':
        assert(current_token.type == Int);
        current_token.type = Float;
        end++;
        break;
      case '0' ... '9':
        if ( current_token.type == String ) {
          end++;
          break;
        }
        if ( current_token.type == None )
          current_token.type = Int;
        end++;
        break;
      //case '$':
      case 'A' ... 'Z':
      case 'a' ... 'z':
        assert(current_token.type == None || current_token.type == String);
        current_token.type = String;
        end++;
        break;
      /*default:*/
        /*current_token.text = strndup(start, end-start);*/
        /*tokenizer.tokens[tokenizer_index] = current_token;*/

        /*current_token = new_token();*/
        /*tokenizer_index++;*/
        /*break;*/
    }


  }
  current_token.text = strndup(start, end-start);
  tokenizer.tokens[tokenizer_index] = current_token;
  tokenizer.size = tokenizer_index + 1;

  return tokenizer;
}

int main (int argc, char *argv[])
{
  //struct Tokenizer t = tokenize("1234");
  struct Tokenizer t = tokenize("string 55 12.456743");

  for (int i = 0; i < t.size; i++) {
    struct Token token = t.tokens[i];
    printf("%d - %s\n", token.type, token.text);
  }
  return 0;
}
