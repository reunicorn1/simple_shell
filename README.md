# Simple Shell

This project is a fulfillment of the requirements of the **ALX Software Engineering Program - Sprint 1**. It involves the creation of a shell program that serves as an intermediary between a user and the operating system, providing a user-friendly interface through the terminal. The shell offers a way for users to interact with various programs and the system itself.

The shell operates by **displaying a prompt**, accepting input from the user, **parsing the user's input** to identify and separate command tokens, **searching for the requested command** within the system's PATH, and then initiating a child process to **execute the specified program**. While the child process runs, the parent process waits for the command to complete. Once the execution is finished, the shell returns to its initial state, ready to accept another prompt from the user.

In essence, this project emulates the functionality of a typical shell program, enabling users to issue commands, interact with programs, and manage their system through a familiar command-line interface.

# How This works
![A flowchart of the simple shell framework](https://postimg.cc/BXy1fBFQ)

### `main`

The `main` function calls `loop` which is an infinite loop function that handles the whole process of shell.

## 1- Displaying the Prompt

### `loop`

Inside the `loop` function a prompt is being displayed and waits for the user to type a certain input.

## 2. Reading the user input

### `recieve_input`

 1. The function take the input from the user using  `getline` 
    function.
 2. It also handles the  **EOF**  condition, once the return value
    form getline function becomes (-1), we check the value inside the
    string in which  `getline`  read data into it, if it’s empty, this
    indicates the **EOF**, so every memory is freed and then we exit
    using the last process return value.
 3. Elsewise, this function returns a string fully edited and ready to
    be parsed and tokanized
   
	   ⚠️  **Memory is allocated —- has to be freed**

## 3- Parsing the command

### `toker`

this function recieves the string from  `recieve_input`

Allocates memory for the array of pointers in which we will create during tokanization (size 10 suitable for 10 pointers to be stored in).
Create an array of pointers and returns an array of pointers to be processed later.
 
⚠️  **Memory is allocated —- has to be freed**

## 4- Creating commands list

### `cmd_list`

this function divides the array of tokens in the same manner as the `strtok` function does but in string level. this function has to be checked in an inner while loop after execution and before freeing. Inspired by how strtok works, this function replaces the element of the array of tokens which has a semicolon with a **NULL**.

This operation will not cause a memory leak since, the token which actually has the semicolon is just a pointer to the string **str** (the output of `getline`), the function keep track of the element after `;` to be given as the next command array when provoked for the second time.

## 5- Searching for the command

### `checkpoint`

`checkpoint` produces the path whether by itself or with the help of function `_which`. it also calls other built-in functions if necessary.

If **arg[0]** equals certain strings which compose the built-in functions we direct the execution into the required built-in function. `checkpoint` returns name of the program, which is again checked before forking, to stop entering the function `execute`.

Elsewise, we pass arg[0] to `_which` function and look for the required path, and edit the string into which **arg[0]** is pointing to and replace with the address fullpath, this returns the required **cmd** "command".

### `_which`

This function is appointed to look for the path using the first argument that is made from the toker function which is **arg[0]**. It works with the function  `checkpoint`

It will look for the required path, and create a string and return it as cmd.

> cmd is a string which is actually the required pathname.

If the required directory from the path is not found, meaning that we passed an argument which is not an executable program nor a built-in function, we will return a signal "**NULL**" so an error , which can be displayed form the `loop` function.

> The error to be displayed will be made from the loop function and
> after it a prompt will be displayed again to return to the initial
> stage.

*Fullpath is dynamically allocated and has to be freed later.*

⚠️  **Memory is allocated —- has to be freed**

## Built-in functions

### `exit`
This function exits using an argument or without. when it exits without it uses the last process return value. All the resources used are freeed before completly exiting the program, so no memory leakage is happening.

### `env`
This function prints all the environement variables that are inherited from the current parent process.

### `setenv`, `unsetenv`
If the environment array (environ) contains a string of the form name=oldvalue, then unsetenv deletes it and setenv replaces oldvalue with newvalue. If name does not exist, then setenv adds name=newvalue to the array.
The function first computes the lengths of the name and value.
It then searches for the specified environment variable (name) within the current environment **environ**.
If the variable is not found, it reallocates memory to accommodate the new value. and a new string is created combining the name and value to be added. The pointer in the **environ** array is updated to point to the newly allocated memory.
If neither name or value is found, a new element is added at the end of the environ array by creating a replica of it but with enlarged, all elements are copied into the replica, and the new element is added at the end plus NULL.

### `alias`

 1. This function prints the complete existing dataset, when `alias`
    command has no arguments or has only `-p` an an argument. in the format **name='value’**
    
 2. **alias name [name2 ...]** This function checks the arguments list argument by argument, token by token, if a token has no ‘=’ among the chars of the string, it searches the dataset and prints only the specified “name” in the known format. if not found it prints nothing.
 
 3. **alias name='value' [...]** This function checks the arguments list, token by token if it has **‘=’** among the chars of the string, it adds the name “before the =”to the array of names and the value which is between double quotes or single quotes, it starts scanning the part after the quotes until it reaches the other quote, if the string finishes without finding the second quote, it adds a space and looks the next token until it finds the closing quote. The value is added to the corresponding index of the name in its own array.

> As a result of this the recive_input has a certain part in which it
> scans the alias data set and replaces arguments which are commands from the list with the corresponding value.

⚠️ **Memory is allocated - has to be freed (two arrays)**

## 6- Creating a child process

the loop function handles the child process creation, through forking.

## 7- Execution of the command

### `execute`

This function handles the execution of the program required inside the child process (if it’s not a built in function). it takes  **cmd**  which is the return value from `checkpoint` and process it using `execve` function.

Since we are calling `execve` function, that means that we are not returning to the main from here, that’s why this is processed inside a child.

> Normally the output of this will be directly displayed into the stdout

## 8- Wait for the command completion

The parent shell (the original process) waits for the child process to complete using functions like `wait` or `waitpid`. This ensures that the shell doesn't display the next prompt until the command finishes executing. this occurs through the `loop` function.

## 9- Returning to the prompt

After the executed command completes, the loop function returns to its initial state, displaying the prompt and waiting for the user to input another command.

## 10- Exiting the Shell

The checkpoint function already handles exiting. **Ctrl+D** and **EOF** condition is handled early on the process in the `recieve_input` function.


### Authors

Reem Osama
Yahia Nasr
