#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct node {
    char textVal[4];
    int length;
    struct node * next;
} word;

void display_dictionary (word *head){
	if (head){
		word * current = head;
		char * print;
		while (current->next != NULL) {
			printf("%s\n", strncpy(print, current->textVal, 4));
			current = current->next;
		}
		printf("\n");
	} else{
		printf("No words currently stored in the dictionary \n\n");
	}
}

void add_word (word * head, char * str, int length){
	word * current = head;
	while (current->next != NULL){
			current = current->next;
	}
	current->next = malloc(sizeof(word));
	strncpy(current->next->textVal, str, 4);
	current->next->length = length-1;
	current->next->next = NULL;
}

void clear_dictionary(word * head){	
	while (head != NULL){
		word * temp = head;
		head = head->next;
		free(temp);
	}
}

void search_insensative(word * head, char * str){
	word * current = head;
	for(int i=0; str[i]; i++){
		str[i] = tolower(str[i]);
	}
	while(current != NULL){
		if(strncmp(current->textVal, str, 4) == 0){
			printf("%s\n\n", current->textVal);
			return;
		}
		current = current->next;
	}
	printf("Could not find a word based upon your criteria\n\n");
}

void search_sensative(word * head, char * str){
	word * current = head;
	while(current != NULL){
		if(strncmp(current->textVal, str, 4) == 0){
			printf("%s\n\n", current->textVal);
			return;
		}
		current = current->next;
	}
	printf("Could not find a word based upon your criteria\n\n");
}


int main(int argc, char **argv)
{
  int words = 10;
	char str_array[10][BUFSIZ];
	int i, j;
	int iter = 0;
	char shortTextVal[BUFSIZ];
	word * head = malloc(sizeof(word));
	head->next = NULL;
	head->textVal[0] = NULL;
	head->length = NULL;
  // used to determine when the application closes
  int exit = 0;
	//
  printf("Welcome, please begin by typing a sentence to fill your dictionary.\n");
  fgets(shortTextVal, sizeof(shortTextVal), stdin);
  j = 0;
  iter = 0;
  for(i = 0; i <= (strlen(shortTextVal)); i++){
    if (shortTextVal[i] == ' ' || shortTextVal[i] == '\0' || shortTextVal[i] == ','){
      str_array[iter][j]  = '\0';
      iter++;
      j=0;
    }
    else {
      str_array[iter][j] = shortTextVal[i];
      j++;
    }
  }
  strncpy(head->textVal, str_array[0], 4);
  head->length = strlen(str_array[0]);
  for(i = 1; i <= iter; i++){
    add_word(head, str_array[i], strlen(str_array[i]));
  }
  printf("\n");
	while (exit != 1){
		printf("Select an option:\n");
    printf("1) Add entry\n");
    printf("2) Search entries (sensative)\n");
    printf("3) Search entries (insensative)\n");
    printf("4) Clear entries\n");
    printf("5) Show dictionary\n");
    printf("6) Exit disctionary application\n\n");
		char selection[BUFSIZ];
		fgets(selection, BUFSIZ, stdin);
		switch(atoi(selection)){
			case 1:
        printf("Enter the new word to be added: ");
				iter++;
				char input[BUFSIZ];
				fgets(input, sizeof(input), stdin);
				printf("%s", input);
				add_word(head, input, strlen(input));
				printf("\n");
				break;
			case 2:
        printf("Search (case sensative)");
        fgets(shortTextVal, sizeof(shortTextVal), stdin);
        search_sensative(head, shortTextVal);
        break;
			case 3:
				printf("Search (case insensative) ");
        fgets(shortTextVal, sizeof(shortTextVal), stdin);
        search_insensative(head, shortTextVal);
        break;
			case 4:
        clear_dictionary(head);
        head = NULL;
				printf("All entries have been cleared! ");
        break;
			case 5:
				display_dictionary(head);
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
