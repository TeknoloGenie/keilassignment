#include <ctype.h>

typedef struct Word {
  char title[18];
  char abbr[5];
  int index;
  int length;
  struct Word *next;
} Word;


Word *add(char *input){
  struct Word* word = (struct Word*) malloc(sizeof(struct Word));
  char abbr[5];
  int length = strlen(input);
  strncpy(abbr, input, 4);
  strcpy(word->title, input);
  word->length = length;
  abbr[5 - 1] = '\0';
  strcpy(word->abbr, abbr);
  word->next = NULL;
  return word;
}