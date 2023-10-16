[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/xR-cYv8r)
# project1
Answer these questions please:
Tell me what this project is about?
Tell me how your thought process for completing the project?
Any issues you came across?

NOTEs: 
- I used /proc for the proc commands, not "proc"
- Exit command: "exit"
- history command: "history"
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
What this project is about:
This project is a simplified unix shell implemented in C. It mimics some of the basic functionalities of a Unix shell Such as:
- reading commands from the user
- Parsing them
- Executing them
In addition, it also supports a number of built in commands such as exit and a custom history feature to display the last 10 commands entered by the user

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Thought Process:

For part one:
my though process was understanding what a simplified UNIX shell shoudl do
It needed to accept commands from the users, parse them, and execute them, as well as handle some built in commands
As we were given the main template, I split it up, starting with the easiest.
I started with main()that would call user_prompt_loop() and that would call get_command(), parse_command(), and execute_command().
I then implemented each

For part two:
I added the proc logic in user_command loop. I knew it would either be exit or proc that I would have to look out for, so I added the logic as an elif under the exit command

For part three:
I had the same thought process for part two. Exept I added extra logic to user_promtp_loop() as that is where the new commands were passed in. 
I also created it in main and passed it in to this function.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Issues Encountered:

1.) Memory Management: One of the challenges was managing memory effectively to prevent memory leaks, especially when storing command history
2.) File operations: At first I implemented the history file to be persistant, in terms of saving data from all runs of the program, which led to seg faults. The persistence feature was then dropped and removed for simplification as well as seeing it was not listed as a requirement in the project document
3.) Parsing commands: Handling various edge cases while parsing the commands was aslo somwhat challenging




