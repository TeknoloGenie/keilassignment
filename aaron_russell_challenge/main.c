#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "word.h"

void print_dictionary (Word *head){
  printf("Printing dictionary...\n");
  printf("------------------------------------------------\n");
	Word * current = head;
  while (current != NULL) {
      printf("%s\n", current->title);
      current = current->next;
  }
  printf("------------------------------------------------\n");
  printf("End of dictionary\n");
}

void Dictionary(struct Word *i, struct Word **head, struct Word **last) {
  struct Word *old, *p;
  p = *head;
  if (!*last) { 
    i->index = 1;
    i->next = NULL;
    *last = i;
    *head = i;
    return;
  }
  old = NULL;
  while (p) {
    if (strcmp(p->title, i->title) < 0) {
      old = p;
      p = p->next;
    } else {
      if (old) {
        i->index = old->index + 1;
        old->next = i;
        i->next = p;
        return;
      }
      p->index = i->index + 1;
      i->next = p;
      *head = i;
      return;
    }
  }
  (*last)->next = i;
  i->next = NULL;
  *last = i;
}


void clear_dictionary(Word * head){	
	while (head != NULL){
		Word * temp = head;
		head = head->next;
		free(temp);
	}
}

void search_insensative(Word * head, char * str){
	Word * current = head;
	for(int i=0; str[i]; i++){
		str[i] = tolower(str[i]);
	}
	while(current != NULL){
		if(strncmp(current->title, str, strlen(str)) == 0){
			printf("Found a word that matches your exact search:\n %s) %s - %d \n", current->abbr, current->title, current->length);
			return;
		} else if (strncmp(current->abbr, str, 4) == 0) {
      printf("Found a similiar word that resembles your search:\n %s) %s - %d \n", current->abbr, current->title, current->length);
			return;
    }
		current = current->next;
	}
	printf("Could not find any word resembling or matching your search\n");
}

void search_sensative(Word * head, char * str){
	Word * current = head;
	while(current != NULL){
		if(strncmp(current->title, str, strlen(str)) == 0){
			printf("Found a word that matches your exact search:\n %s) %s - %d \n", current->abbr, current->title, current->length);
			return;
		} else if (strncmp(current->abbr, str, 4) == 0) {
      printf("Found a similiar word that resembles your search:\n %s) %s - %d \n", current->abbr, current->title, current->length);
			return;
    }
		current = current->next;
	}
	printf("Could not find any word resembling or matching your search\n");
}

int main(int argc, char **argv) {
  // used to determine when the application closes
	//initialize the sentence variable
  char searchQuery[18];
  int exit = 0;
  long user_input_sentence[BUFSIZ];
  printf("Welcome, enter your sentence to begin:\n");
  fgets(user_input_sentence, BUFSIZ, stdin);
  int words = 0;
  const char delim[] = " .,;:!-\n\r";
  struct Word *head = NULL;
  struct Word *last = NULL;
  char *token = strtok(user_input_sentence, delim);
  
  while (token != NULL) {
    Word *word = add(token);
    Dictionary(word, &head, &last);
  
    token = strtok(NULL, delim);
    words += 1;
  }
    printf("\n");

	while (exit != 1) {
    char searchQuery[18];
    printf("Select an option:\n");
    printf("1) Add entry\n");
    printf("2) Search entries (sensative)\n");
    printf("3) Search entries (insensative)\n");
    printf("4) Clear entries\n");
    printf("5) Show dictionary\n");
    printf("6) Exit dictionary application\n\n");
		char selection[BUFSIZ];
		fgets(selection, BUFSIZ, stdin);
		switch(atoi(selection)){
			case 1:
        printf("Enter some more word(s) seperated by spaces, commas or puncuation\n");
        fgets(user_input_sentence, BUFSIZ, stdin);
				char *token = strtok(user_input_sentence, delim);
  
        while (token != NULL) {
          Word *word = add(token);
          Dictionary(word, &head, &last);
        
          token = strtok(NULL, delim);
          words += 1;
        }
				printf("%s \n", user_input_sentence);
				break;
			case 2:
        printf("Search (case sensative)\n");
        fgets(searchQuery, sizeof(searchQuery), stdin);
        search_sensative(head, searchQuery);
        break;
			case 3:
        printf("Search (case insensative)\n");
        fgets(searchQuery, sizeof(searchQuery), stdin);
        search_insensative(head, searchQuery);
        break;
			case 4:
        clear_dictionary(head);
        head = NULL;
				printf("All entries have been cleared!\n");
        break;
			case 5:
				print_dictionary(head);
				break;
			case 6:
				exit = 1;
				break;
		}
  }
    //create an array of nodes where each node is the word
    //each node should store the words length and first 4 letters of the word including the original word
    //sort the linked list of nodes in alphabetical order
    //prompt user the current amount of node stored and offer the following choices [Add Entry, Clear List and Search]
    //if Add Entry then prompt the user for more words, inserting them in alphabetical order
    //if Clear List then clear the list of nodes and 
	return 0;
}
