#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MANATEE_FILE "manatee.dat"

// The Manatee File Standard dictates that a manatee file must
// consist of 27 lines each containing 61 ASCII characters
// (including the new line character)
#define MANATEE_WIDTH 61
#define MANATEE_HEIGHT 27
#define MANATEE_SIZE MANATEE_WIDTH * MANATEE_HEIGHT

#define MAX_MESSAGE_LEN 80

void the_secret_of_the_manatee() {
  FILE *secret_file = fopen("secret.txt", "r");
  if(secret_file != NULL) {
    char buffer[256];
    while(fgets(buffer, 256, secret_file) != NULL) {
      printf(buffer);
    }
    fclose(secret_file);
  }
}

void print_message(char *message) {
  unsigned len, ii;
  
  // display the message
  len = strlen(message);
  printf("\n  ");
  for(ii = 0; ii < len; ii++) printf("*"); printf("\n");
  printf(" *"); for(ii = 0; ii < len; ii++) printf(" "); printf("*\n");
  printf("* "); printf(message); printf(" *\n");
  printf(" *"); for(ii = 0; ii < len; ii++) printf(" "); printf("*\n");
  printf("  "); for(ii = 0; ii < len; ii++) printf("*"); printf("\n");
}

int manatee_session(FILE *fptr) {
  // For storing a message, from stdin
  // +1 for the null terminator
  // +1 for the new line character
  char message_buffer[MAX_MESSAGE_LEN + 2];

  // For storing the contents of a manatee file
  char manatee_buffer[MANATEE_SIZE];


  long fsize;
  char *pos;
  char c;

  fprintf(stderr, "Enter your message => ");
  if(fgets(message_buffer, sizeof(message_buffer), stdin) == NULL) {
    fprintf(stderr, "The manatee is frightened and swims away.\n");
    return 1;
  }
  if((pos=strchr(message_buffer, '\n')) != NULL) {
    *pos = '\0';
  } else {
    fprintf(stderr, "The manatee is frightened and swims away.\n");
    return 1;
  }
  print_message(message_buffer);

  // Read the manatee from the file
  // Thanks: https://stackoverflow.com/questions/174531/how-to-read-the-content-of-a-file-to-a-string-in-c
  bzero(manatee_buffer, MANATEE_SIZE);
  fseek(fptr, 0, SEEK_END);
  fsize = ftell(fptr);
  rewind(fptr);
  fread(manatee_buffer, sizeof(char), fsize, fptr);
  fwrite(manatee_buffer, sizeof(char), MANATEE_SIZE, stdout);

  // Return 0 if all went well
  return 0;
}

int main(int argc, char **argv) {
  while(1) {
    // Open the manatee file
    FILE *fptr;
    fptr = fopen(MANATEE_FILE, "r");
    if(fptr == NULL) {
      fprintf(stderr, "Your manatee file has gone missing.\n");
      fprintf(stderr, "Contact m4n4t33_f4n@yahoo.com for a replacement manatee file.\n");
      fprintf(stderr, "(Please write, \"Regarding Missing Manatee File\" in the subject.)\n");
      exit(1);
    }

    if(manatee_session(fptr) != 0) {
      fclose(fptr);
      exit(1);
    }

    // Clean up the file
    fclose(fptr);
  }
  return 0;
}
