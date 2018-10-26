#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 80
#define MAXARG 20

void background(char *cmd);

//The main is facilitating what I would describe as the event loop.
//It prints the prompt mysh$ and waits for a command. 
//The command can only be a max of 80 chars total before overflow 
//of the cmd line. Once a command is recived it makes an initial 
//look to see if the command matches the exit command. If it does,
//the shell exits and ends. If the command is somthing other than an 
//exit command then the loop calls the function background to facilitate 
//using the command called. 
int main()
{
  //Defined the max length of the command given
	char cmd[MAXLINE];

  //Event loop to wait for a command
  //The fgets reads the line
	for (; ;)
	{
		printf("mysh$ ");
		fgets(cmd, MAXLINE, stdin);
    //Parse the command given. If it matches "exit\n" then exit the shell
    //Otherwise call background to run the command called.
		if (strcmp(cmd, "exit\n") == 0)
			return EXIT_SUCCESS;
		background(cmd);
	}

  //Exit if the loop failed somehow.
	return EXIT_FAILURE;
}

//background runs the command called from the main event loop. It starts 
//by defining variables to start a new process. Then it defines an 
//array of strings to tokenize the command sent to capture the input
//parameters the user may have sent. Its important to note that the 
//max number of arguments that can be taken is 20 args. 
//After capturing the arguments in the while loop, The function
//creates a new process to run the commmand. Within the fork, the command
//is called. If the command passed by the user wasn't a valid command then 
//the process exits and it goes back to the event loop waiting for another 
//command. If the command was a valid one then the command is executed and 
//upon completion the program ends the fork. The program then returns back
//to the event loop waiting for a new command.
void background(char *cmd)
{
  //Defined variables for the new process
	int pid, i=0, status;
  //Define the max number of arguments that can be passed.
	char *argv[MAXARG];

  //Tokenize the entire command string to extract the command from the 
  //cmd string. 
	argv[i++] = strtok(cmd, "\t \n");
	while ( i<MAXARG && 
	 	(argv[i++] = strtok(NULL, "\t \n")) != NULL);

  //Start a new process. Within the new process check if your fork = 0
  //If it does, run the command with the prescribed arguments. 
	if ((pid = fork()) == 0)			
	{
		execvp (argv[0], argv);		
    //exit signal for the wait function at the end of this function
		exit(EXIT_FAILURE);			
	}
  //If the fork failed to create inform the user that the command failed
  //to run because of the failed fork.
	else if (pid < 0)
	{
		fprintf(stderr, "fork failed\n");
		perror("background process: ");
	}

  //wait for the command to be finished running and then leave the function back to main
	wait(&status);
}

