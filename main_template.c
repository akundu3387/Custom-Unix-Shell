/*
project: 01
author:Arjun Kundu 
email: akundu2@umbc.edu
student id: NP70299
description: a simple linux shell designed to perform basic linux commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "utils.h"
#define MAX_HISTORY 10 //number of commands that will be stored in history file

/*
In this project, you are going to implement a number of functions to 
create a simple linux shell interface to perform basic linux commands
*/

/* 
DEFINE THE FUNCTION PROTOTYPES
*/
void user_prompt_loop();
char* get_user_command();
char** parse_command(char *command);
void execute_command(char **parsed_command);
void read_proc_file(char *file_path); //created function to read from /proc filesystem
void free_history(char **history,int count);

int main(int argc, char **argv)
{
    /*
    Write the main function that checks the number of argument passed to ensure 
    no command-line arguments are passed; if the number of argument is greater 
    than 1 then exit the shell with a message to stderr and return value of 1
    otherwise call the user_prompt_loop() function to get user input repeatedly 
    until the user enters the "exit" command.
    */

    /*
    ENTER YOUR CODE HERE
    */
    // Check for command-line arguments
    if (argc > 1) {
        fprintf(stderr, "The shell does not accept command line arguments.\n");
        return 1;
    }

    // Initialize history
    char *history[MAX_HISTORY];
    int history_count = 0; // Count of lines read

    // opening/creating .421sh file
    FILE *history_file;
    char *home_directory = getenv("HOME");
    char history_path[1024];

    snprintf(history_path, sizeof(history_path), "%s/.421sh", home_directory);
    history_file = fopen(history_path, "a+");  // Open for reading and appending

    // Read lines from the history file into the history array
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, history_file)) != -1 && history_count < MAX_HISTORY) {
        line[strcspn(line, "\n")] = 0;  // Remove trailing newline
        history[history_count] = strdup(line);
        history_count++;
    }

    free(line);
    rewind(history_file);  // Reset the file pointer to the beginning

    // Start the user prompt loop
    user_prompt_loop();

    // Free the history
    free_history(history, history_count);

    // Close the history file
    fclose(history_file);

    return 0;
}

/*
user_prompt_loop():
Get the user input using a loop until the user exits, prompting the user for a command.
Gets command and sends it to a parser, then compares the first element to the two
different commands ("/proc", and "exit"). If it's none of the commands, 
send it to the execute_command() function. If the user decides to exit, then exit 0 or exit 
with the user given value. 
*/

void user_prompt_loop()
{
    // initialize variables

    /*
    loop:
        1. prompt the user to type command by printing >>
        2. get the user input using get_user_command() function 
        3. parse the user input using parse_command() function 
        Example: 
            user input: "ls -la"
            parsed output: ["ls", "-la", NULL]
        4. compare the first element of the parsed output to "/proc"and "exit"
        5. if the first element is "/proc" then you have the open the /proc file system 
           to read from it
            i) concat the full command:
                Ex: user input >>/proc /process_id_no/status
                    concated output: /proc/process_id_no/status
            ii) read from the file line by line. you may user fopen() and getline() functions
            iii) display the following information according to the user input from /proc
                a) Get the cpu information if the input is /proc/cpuinfo
                - Cpu Mhz
                - Cache size
                - Cpu cores
                - Address sizes
                b) Get the number of currently running processes from /proc/loadavg
                c) Get how many seconds your box has been up, and how many seconds it has been idle from /proc/uptime
                d) Get the following information from /proc/process_id_no/status
                - the vm size of the virtual memory allocated the vbox 
                - the most memory used vmpeak 
                - the process state
                - the parent pid
                - the number of threads
                - number of voluntary context switches
                - number of involuntary context switches
                e) display the list of environment variables from /proc/process_id_no/environ
                f) display the performance information if the user input is /proc/process_id_no/sched
        6. if the first element is "exit" the use the exit() function to terminate the program
        7. otherwise pass the parsed command to execute_command() function 
        8. free the allocated memory using the free() function
    */

    /*
    Functions you may need: 
        get_user_command(), parse_command(), execute_command(), strcmp(), strcat(), 
        strlen(), strncmp(), fopen(), fclose(), getline(), isdigit(), atoi(), fgetc(), 
        or any other useful functions
    */

    /*
    ENTER YOUR CODE HERE
    */
    char *command;
    char **parsed_command;

    while (1) {
        printf(">> ");
	//Read users command input
        command = get_user_command();
	//Check if command is empty or all whitespaces
	if(command == NULL || count_spaces(command) == strlen(command)){
	    free(command);
	    continue;
	}
	//Call parse_command to read the commands into its components
        parsed_command = parse_command(command);
	//Handle the Exit command
        if (strcmp(parsed_command[0], "exit") == 0) {
            if (parsed_command[1] == NULL) {
                exit(0);
            } else {
                char *end;
                int status = strtol(parsed_command[1], &end, 10);
                if (*end == '\0') {
                    exit(status);
                } else {
                    fprintf(stderr, "Invalid argument to exit: %s\n", parsed_command[1]);
                }
            }
	}else if (strcmp(parsed_command[0], "/proc") == 0) {
            //Part2: New code for handling /proc
            if(parsed_command[1]) {
                char filepath[256] = "/proc/"; //initilizes filepath for /proc directory
                strcat(filepath, parsed_command[1]);//add file name to filepath
                if (parsed_command[2]) {  //handle inputs like "/proc/1/status"
                    strcat(filepath, "/");
                    strcat(filepath, parsed_command[2]);
                }
                read_proc_file(filepath);//read/display contents of specified /proc file
            } else {
                fprintf(stderr, "Invalid '/proc' command usage. Missing file or parameter.\n");
            }

        } else {
            //All other commands,  Pass to execute_command()
            execute_command(parsed_command);
        }

        // Freeing allocated memory for command and parsed_command
        free(command);
        for (int i = 0; parsed_command[i]; i++) {
            free(parsed_command[i]);
        }
        free(parsed_command);
    }

}

/*
get_user_command():
Take input of arbitrary size from the user and return to the user_prompt_loop()
*/

char* get_user_command()
{
    /*
    Functions you may need: 
        malloc(), realloc(), getline(), fgetc(), or any other similar functions
    */

    /*
    ENTER YOUR CODE HERE
    */
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);

    if (nread == -1) {
        // Handle the error or exit
        perror("getline");
        exit(EXIT_FAILURE);
    }

    return line;
}

/*
parse_command():
Take command grabbed from the user and parse appropriately.
Example: 
    user input: "ls -la"
    parsed output: ["ls", "-la", NULL]
Example: 
    user input: "echo     hello                     world  "
    parsed output: ["echo", "hello", "world", NULL]
*/

char **parse_command(char *command)
{
    /*
    Functions you may need: 
        malloc(), realloc(), free(), strlen(), first_unquoted_space(), unescape()
    */

    /*
    ENTER YOUR CODE HERE
    This function will take in the command string as an argument and return an aray of strings
    where each string is a seperate command or argument. 
    To implement, I will be using utilizing utils.c, especially the unescaped function
    */
    int bufferSize = 64;  // Initial buffer size for tokens array
    int position = 0;  // Position to insert the next token
    char **tokens = malloc(bufferSize * sizeof(char*));  // Dynamic array to hold tokens
    char *unescaped_input = unescape(command, stderr);  // Unescaped input using utils.c function
    char *token;  // Individual tokens

    // Check for memory allocation failure
    if (!tokens || !unescaped_input) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Tokenize the unescaped input string
    token = strtok(unescaped_input, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = strdup(token);
        position++;

        // Resize tokens array if it's full
        if (position >= bufferSize) {
            bufferSize += 64;
            tokens = realloc(tokens, bufferSize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " \t\r\n\a");
    }

    tokens[position] = NULL;  // Null-terminate the tokens array

    free(unescaped_input);  // Free the unescaped input string
    unescaped_input = NULL;
    return tokens;


}

/*
execute_command():
Execute the parsed command if the commands are neither /proc nor exit;
fork a process and execute the parsed command inside the child process
*/

void execute_command(char **args)
{
    /*
    Functions you may need:
        fork(), execvp(), waitpid(), and any other useful function
    */

    /*
    ENTER YOUR CODE HERE
    */
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("Shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Forking error
        perror("Shell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

/*read_proc_file
This function serves to read from the /proc filesystem
Because as per Part 2 requirments:  we dont have parse the information read from the /proc files
Therefore, this function will simply open the file and dump its contents to stdout
*/

void read_proc_file(char *file_path) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    fp = fopen(file_path, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while ((nread = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}

void free_history(char **history, int count) {
    for (int i = 0; i < count; i++) {
        free(history[i]);
    }
}
