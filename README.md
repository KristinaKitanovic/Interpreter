# Project Summary

The Interpreter is a simple C++ program designed to parse and execute predefined scripts or commands. It provides a basic framework for interpreting command-line input, processing it, and executing corresponding actions. The project demonstrates fundamental concepts of interpreters, including parsing, tokenization, and command execution.

This interpreter can be extended to support more complex commands and features, making it a useful tool for learning about interpreter design and command processing in C++. It is built with the intent to be a simple, yet flexible base for further expansion, allowing developers to experiment with different parsing strategies and execution models.

Key features include:
- Command parsing and execution
- Basic error handling for invalid commands
- Extensibility for adding new commands or features
- Written entirely in C++ for performance and learning purposes

## Running the Project

To run this project on your machine, follow these steps:

1. Open your terminal (e.g., PowerShell, Git Bash, or Command Prompt).
2. Clone the repository from GitHub using the following command:

```bash
git clone https://github.com/KristinaKitanovic/Interpreter.git
```
3. Open the project in Visual Studio by opening the .vcxproj file.

## Supported Commands

This interpreter supports the following commands:

### `echo`
**Format:**  
`echo [argument]`  
**Description:**  
Echoes the input string or the content of the file to the output without any modifications. 
**Options:**  
None.
**Example**
$ echo "Hello World!"
$ echo filename.txt 
$ echo
Hello World!
How are you?
EOF


---

### `prompt`
**Format:**  
`prompt [argument]`  
**Description:**  
Changes the prompt for the interpreter to the string provided in the argument, enclosed in quotes.  
**Options:**  
None.
**Example**
$ prompt "&"


---

### `time`
**Format:**  
`time`  
**Description:**  
Prints the current time from the system clock to the output.  
**Options:**  
None.
**Example**
$ time


---

### `date`
**Format:**  
`date`  
**Description:**  
Prints the current date from the system clock to the output.  
**Options:**  
None.
**Example**
$ time

---

### `touch`
**Format:**  
`touch [filename]`  
**Description:**  
Creates a file with the specified name and an empty content in the current directory. If the file already exists, an error message is displayed, and no other action is taken.  
**Options:**  
None.
**Example**
$ touch newfile.txt

---

### `truncate`
**Format:**  
`truncate [filename]`  
**Description:**  
Deletes the content of the specified file in the current directory.  
**Options:**  
None.
**Example**
$ truncate file.txt

---

### `rm`
**Format:**  
`rm [filename]`  
**Description:**  
Removes the specified file from the file system in the current directory.  
**Options:**  
None.
**Example**
$ rm file.txt

---

### `wc`
**Format:**  
`wc -opt [argument]`  
**Description:**  
Counts words or characters in the text read from the input stream and prints the result to the output. Words are sequences of characters separated by spaces.  
**Options:**  
- `-w` Counts words  
- `-c` Counts characters
**Example**
$ wc -w "Hello"
$wc -c "Hello"
$ wc -w input.txt
$ wc -w
Hello World!
How are you?
EOF

---

### `tr`
**Format:**  
`tr [argument] what [with]`  
**Description:**  
Finds all occurrences of the string `what` (enclosed in quotes) in the input stream and replaces them with the string `with` (also enclosed in quotes). If `with` is not provided, occurrences of `what` are removed from the input text.  
**Options:**  
None.
**Example**
 $ tr "How are you" "you" "we"

---

### `head`
**Format:**  
`head -ncount [argument]`  
**Description:**  
Transfers the first `n` lines of text from the input stream to the output and ignores the rest.  
**Options:**  
- `-n` Specifies the number of lines to transfer. The value immediately following `-n` (without spaces) must be a number, indicating the number of lines.
**Example**
 $ head -n3 file.txt

---

### `batch`
**Format:**  
`batch [argument]`  
**Description:**  
Interprets the input stream as a sequence of commands, each on a new line, and processes them one by one as if they were read from the console (batch processing). If any command encounters an error, it prints the error message and continues with the next command. The input stream can contain any command, including the `batch` command itself. Recursion is allowed and should be used with caution.  
**Options:**  
None.
**Example**
 $ batch
 time 
 date 
 EOF
 

### Pipes 

The interpreter supports the concept of pipes, allowing you to chain multiple commands together. Each command in a pipeline has its output connected to the next command's input. This means that every character output by the first command is passed as input to the second command, maintaining the order of characters. 

The pipe symbol (`|`) is used to connect commands in a pipeline.

**Example:**

The following command line contains three commands connected in a pipeline:
```bash
time | tr ":" "." | wc -c > time.txt

