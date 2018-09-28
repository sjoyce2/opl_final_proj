/*
Outline of a shell
*/

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80
#define TRUE 80

char** getInput();
char** parseInput(char*);
void dispOutput(char**);

int main(int argc, char* argv[])
{
  //A pointer to an array of pointers to char.  In essence, an array of 
  //arrays.  Each of the second level arrays is a c-string. These hold
  //the command line arguments entered by the user.
  //as exactly the same structure as char* argv[]
  char **args  = (char**) malloc(5*sizeof(char*));
  char **hist;
  int histCount;

  pid_t pid;
  
  while (TRUE)
  {
     printf("myShell> ");
     fflush(stdout);
     args = getInput();
     // dispOutput(args);
     //if the user has entered "quit" break out of the loop.
     if (!strcmp(args[0], "quit")) {
       break;
     }
     // fork a child process using fork()
     pid = fork();
     // child process invokes execvp()
     if (pid == 0) {
       execvp(args[0], args);
     }
     // if command included &, parent will wait()
     if (strstr(args[2], "&")) {
       wait(NULL);
     }

     if (!strcmp(args[0], "history")) {
       if (!strcmp(args[1], "!!")) {
	 if (histCount == 0) {
	   printf("There is no history");
	 } else if (histCount < 10) {
	   printf("%s", hist[histCount - 1]);
	 } else {
	   printf("%s", hist[9]);
	 }
       } else if (strstr(args[1], "!")) {
	 // find n and show last n commands
	 char num = args[1][1];
	 int histNum = num + 0;
	 if (histNum == 1 && args[1][2] == '0') {
	   histNum = 10;
	 }
	 for (int i = 0; i < histNum; i++) {
	   printf("%s", hist[i]);
	 }
       }
     } else {
       printf("Error: Invalid command");
     }
  }
  return 0;
}

/*
Reads input string from the key board.   
invokes parseInput and returns the parsed input to main
*/
char** getInput()
{
  char **userInput = (char**) malloc(5*sizeof(char*));
  char cmdText[80];
  fgets(cmdText, 80, stdin);
  userInput = parseInput(cmdText);
  return userInput;
}  

/*
inp is a cstring holding the keyboard input
returns an array of cstrings, each holding one of the arguments entered at
the keyboard. The structure is the same as that of argv
Here the user has entered three arguements:
myShell>cp x y
*/ 
char** parseInput(char* inp)
{
  char **args = (char**) malloc(5*sizeof(char*));
  char *tmp;
  int tmpCount = 0;
  int cmdCount = 0;
  tmp = (char*) malloc(10*sizeof(char));

  for (int i = 0; i < strlen(inp); i++) {
    if (inp[i] == ' ') {
      //add tmp to args
      tmp[tmpCount] = '\0';
      args[cmdCount] = tmp;
      tmpCount = 0;
    } else if (inp[i] == '\0') {
      // add tmp to args and break;
      tmp[tmpCount] = '\0';
      args[cmdCount] = tmp;
      tmpCount = 0;
      break;
    } else {
      // add inp[i] to tmp
      tmp[tmpCount] = inp[i];
      tmpCount++;
    }
  }
  return args;
} 
 
/*
Displays the arguments entered by the user and parsed by getInput
*/
void dispOutput(char** args)
{
  for (int i = 0; i < sizeof(args); i++) {
    printf("%s", args[i]);
  }
}