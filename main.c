/*
About this program:
- This program counts words.
- The specific words that will be counted are passed in as command-line
  arguments.
- The program reads words (one word per line) from standard input until EOF or
  an input line starting with a dot '.'
- The program prints out a summary of the number of times each word has
  appeared.
- Various command-line options alter the behavior of the program.

E.g., count the number of times 'cat', 'nap' or 'dog' appears.
> ./main cat nap dog
Given input:
 cat
 .
Expected output:
 Looking for 3 words
 Result:
 cat:1
 nap:0
 dog:0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "smp0_tests.h"

#define LENGTH(s) (sizeof(s) / sizeof(*s))

#define malloc_size 100

/* Structures */
typedef struct {
  char *word;
  int counter;
} WordCountEntry;


int process_stream(WordCountEntry entries[], int entry_count)
{
  short line_count = 0;
  char buffer[30];
//question 3-4
  while (fgets(buffer,sizeof(buffer),stdin)) {
    if (*buffer == '.')
      break;
 
    //change the last letter in buffer to '\0'
    for(int j=0;j<sizeof(buffer);j++){
      if(buffer[j]=='\n'){
        buffer[j]='\0';
      }
    }

    //handle space 

      char *token; 
      token =strtok(buffer, " ");
      while( token != NULL ) {  
          //input the entires
        int i =0;
          while (i < entry_count) {
            if (!strcmp(entries[i].word, token))
                entries[i].counter++;
              i++;
            }
            //using srtok() to seperate words
          token = strtok(NULL, " ");
      }
    
    line_count++;
  }
  return line_count;
}


void print_result(WordCountEntry entries[], int entry_count)
{
  fprintf(stdout,"Result:\n");
  int i = 0;
  //question 2-5
  while (entry_count-- > 0) {
    fprintf(stdout,"%s:%d\n", entries[i].word, entries[i].counter);
    i++;
  }

}


void printHelp(const char *name)
{
  fprintf(stderr,"usage: %s [-h] <word1> ... <wordN>\n", name);
}


int main(int argc, char **argv)
{
  const char *prog_name = *argv;
  int print_file_indicator = 0;

  //question 3-3 malloc allocation
    WordCountEntry *entries = (WordCountEntry*) malloc(malloc_size * sizeof(WordCountEntry));


  int entryCount = 0;
  char *FILENAME;

  /* Entry point for the testrunner program */
  if (argc > 1 && !strcmp(argv[1], "-test")) {
    run_smp0_tests(argc - 1, argv + 1);
    free(entries);  
    return EXIT_SUCCESS;
  }
//Question 2-2 : solve entrycount problem
argv++;

  while (*argv != NULL) {
    if (**argv == '-') {

      switch ((*argv)[1]) {
        case 'h':
          printHelp(prog_name);
          break;  

        case 'f':  
        printf("%s\n", (*argv) + 2);
          FILENAME = (*argv) + 2;
          // for open file in line 172
          print_file_indicator = 1;
          break;

        default:
          fprintf(stderr,"%s: Invalid option %s. Use -h for help.\n",
                 prog_name, *argv);
          
      }
    } 


    else {
      if (entryCount < malloc_size) {
        entries[entryCount].word = *argv;
        entries[entryCount++].counter = 0;
      }
    }
    argv++;
  }



  if (entryCount == 0) {
    fprintf(stderr,"%s: Please supply at least one word. Use -h for help.\n",
           prog_name);
    free(entries);
    return EXIT_FAILURE;
  }
  if (entryCount == 1) {
    fprintf(stdout,"Looking for a single word\n");
  } else {
    fprintf(stdout,"Looking for %d words\n", entryCount);
  }

  process_stream(entries, entryCount);
  print_result(entries, entryCount);

  //question 3-2: print file condition
  if(print_file_indicator == 1) {
    //open a file
    FILE *fp=fopen(FILENAME,"w");
 
    //re-run a previous code from line 161 to 165
  if (entryCount == 1) {
    fprintf(fp,"Looking for a single word\n");
  } else {
    fprintf(fp,"Looking for %d words\n", entryCount);
  }
  
  //print counting result :
    fprintf(fp,"Result:\n");
    int i = 0;
    //get how many number need to print 
    int print_entry_count = entryCount;
    //using while loop to print result
    while (print_entry_count-- > 0) {
      // print thr word and the counter
        fprintf(fp,"%s:%d\n", entries[i].word, entries[i].counter);
    i++;
  }

     // close the file 
    fclose(fp);
  }

  // releasre the memory
  free(entries);
  return EXIT_SUCCESS;
}
