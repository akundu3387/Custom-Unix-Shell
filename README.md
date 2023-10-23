# Custom Unix Shell

**Summary:**

In this project, I developed a fully functional Unix/Linux shell program in C, fulfilling three main objectives. 

First:

- I constructed a rudimentary shell that displays a user prompt for command input, handles various command line arguments, and manages memory efficiently
- This base version also included features like parsing user input and offering an 'exit' command with optional argument-based behavior

Second: 

- I extended the shell's functionality to interface with the Linux /proc filesystem, allowing it to read specific files and present the kernel data to the user without requiring additional parsing. 

Lastly:

- I enhanced the shell's capabilities by implementing command history tracking. All executed commands are stored in a hidden file (.421sh) located in the user's home directory
- I created a special '>> history' command was added to display the last ten commands entered by the user. 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


**NOTES: **
- I used /proc for the proc commands, not "proc"
- Exit command: "exit"
- history command: "history"
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





