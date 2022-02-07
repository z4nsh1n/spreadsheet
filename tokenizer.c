#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

enum Type {
  None,
  Int,
  Float,
  String,
  Add,

};

struct Token {
  enum Type type;
  char* text;
  union {
    float f;
    int i;
    char *c;
  } value;
};

struct Token new_token(void) {
  struct Token t = {
    None,
    0
  };

  return t;
}

struct Tokenizer {
  int index;
  size_t size;
  struct Token *tokens;
};

struct Tokenizer new_tokenizer(size_t size) {
  struct Tokenizer tokenizer = {
    0,
    size,
    malloc(sizeof(struct Token) * size),
  };

  return tokenizer;
}

struct Token end_token(struct Tokenizer *tok, struct Token *t, char * text) {
  t->text = text;
  tok->tokens[tok->index] = *t;
  tok->index++;

  return new_token();
}

struct Tokenizer tokenize(char *input) {
  struct Tokenizer tokenizer = new_tokenizer(50);
  struct Token current_token = new_token();

  //int tokenizer_index = 0;
  
  char *start = input;
  char *end = start;

  while (*end != '\x0') {
    switch (*end) {
      case '+':
        if (current_token.type != None) {
          current_token = end_token(&tokenizer, &current_token, strndup(start, end-start));
          start = end;
        }
        current_token.type = Add;
        end++;
        current_token = end_token(&tokenizer, &current_token, strndup(start, end - start));
        start = end;
        break;
      case ' ':
      case '\t':
      case '\r':
      case '\n':
        if (current_token.type == None) {
          end++;
          start=end;
          break;
        }
        current_token = end_token(&tokenizer, &current_token, strndup(start, end-start));
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
    }


  }
  end_token(&tokenizer, &current_token, strndup(start, end-start));

  return tokenizer;
}


int main (int argc, char *argv[])
{
  //struct Tokenizer t = tokenize("1234");
  struct Tokenizer t = tokenize("12+10");

  for (int i = 0; i < t.index; i++) {
    struct Token token = t.tokens[i];
    printf("%d - %s\n", token.type, token.text);
  }
  return 0;
}

// [Int, Add, Int]
