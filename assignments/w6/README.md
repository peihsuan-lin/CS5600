# Multiprocessing in C
## Task 1
Generate random small text strings using genRand-lin.c and store 10,000 random words to output.ttxt
## Task 2
Read output.txt into the self-defined queue.c data structure. Code implementaion is in main.c and store in a global variable **word_queue**

## Task 3
Involves creating child and parent processes to handle batches of words concurrently while implementing IPC for efficient data exchange.
### Parent Process Responsibilities:
The parent process is responsible for writing batches of words into the pipe.
After writing the words, the parent process waits for the child process to complete its execution before proceeding further.
### Child Process Responsibilities:
The child process reads words from the pipe, which were written by the parent process.
Once the child process reads a batch of words, it executes a cipher program to process the words.
After processing the words, the results are written to individual output files named based on the batch ID.

### Execution Flow

1. The main program reads words from an input file and stores them in a queue data structure. 
2. For each batch of words, a child process is created to handle the processing concurrently. 
3. Each child process reads words from the pipe, executes the cipher program, and writes the results to individual output files. 
4. The parent process waits for all child processes to complete their execution before terminating.