#include <stdio.h>
#include <stdbool.h>

enum CellType {
  Int,
  Float,
  String,
  //Ref,
  Formula,
  Empty,
};

typedef struct Cell {
  enum CellType type;
  char *input;

  union {
    float f;
    int n;
    char *str;
    //char *ref;
    char *form;
  };
} Cell;

struct Sheet {
  Cell cells[5][26];
} sheet;

void init_sheet(struct Sheet *sh) {

  for (int i=0; i<5; i++) {
    for (int j=0; j<26; j++) {
      sh->cells[i][j].type = Empty;
    }
  }
}

void display_sheet(struct Sheet *sh) {

  for (int i=0; i<5; i++) {
    for (int j=0; j<26; j++) {
      switch (sh->cells[i][j].type) {
        case Empty:
          printf(".");
          break;
        case Int:
          printf("%d ", sh->cells[i][j].n);
          break;
        case String:
          printf("%s ", sh->cells[i][j].str);
          break;
      }
    }
    printf("\n");
  }

}

void eval_cell(Cell *cell) {
  int v = atoi("12");
}

int main (int argc, char *argv[])
{
  init_sheet(&sheet);

  sheet.cells[0][0].n = 12;
  sheet.cells[0][0].type = Int;
  sheet.cells[0][1].str = "$A0";
  sheet.cells[0][1].type = String;

  display_sheet(&sheet);
  return 0;
}
