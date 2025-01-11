<h1> 42Berlin_GetNextLine </h1>
The aim of this project is to make a function that returns a lineending with a newline, read from a file descriptor.



![image](https://github.com/user-attachments/assets/0effd645-7751-4350-a69f-51dd82640b5b)


Reading a line on a fd is way often a tedious activity. This task is crucial to understand for a future programmer since much of the time is based on manipulating files for data management and persistence. This project consists of coding a function that returns one line at a time from a text file.

Get_Next_Line Submission

When submitting the project, requiriing the following 3 files plus the 3 bonus ones, named the same plus _bonus.

    get_next_line.c
    get_next_line_utils.c
    get_next_line.h


--- 


<h2>Description</h2>

The aim of this project is to make a function that returns a lineending with a newline, read from a file descriptor. For deeper understanding of the project aims, take a look at this link.
Return Values
Value 	Retun
1 	When it reads a line
0 	when it finished reading a file
-1 	when an error occurs
Download

Feel free to download the project:

    git clone https://github.com/RenWro/42Berlin_GetNextLine.gif

Using The Program

Compile the program:

    gcc -Wall -Wextra -Werror -g get_next_line.c get_next_line_utils.c main.c -o gnl

Or compile the bonus:

    gcc -Wall -Wextra -Werror -g get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus


To run the program:

    ./gnl text1.txt

or
    
    ./gnl text2.txt


What is Valgrind?

Valgrind is a powerful debugging and profiling tool primarily used for memory-related issues in programs written in C and C++. It helps developers detect:

    Memory Leaks: Memory that is allocated but never freed.
    Invalid Memory Access: Accessing memory that was already freed or not allocated.
    Uninitialized Variable Use: Using variables that were not properly initialized.
    Thread and Concurrency Issues: Detecting race conditions in multithreaded programs.

It is particularly useful in ensuring your program adheres to good memory management practices and prevents crashes.

To use it, the following code is useful:

    gcc -Wall -Wextra -Werror -g get_next_line.c get_next_line_utils.c main.c -o gnl

Followed by

    valgrind --leak-check=full ./gnl text1.txt

or

    valgrind --leak-check=full ./gnl_bonus text1.txt


Testing with Multiple File Descriptors (Bonus)

One of the main features of the bonus is support for multiple file descriptors. You can test this functionality by modifying your main_bonus.c to open more than one file simultaneously. Example:

Compliling and executing:

        gcc -Wall -Wextra -Werror -g get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus

        ./gnl_bonus

---
<h1>About it all</h1>

Static Buffer as a memory keeper

In this get_next_line function, we use a static variable like this

char *get_next_line(int fd)
{
    static char *buffer;
    // ... rest of the function
}

This buffer isn't just any ordinary variable. Let's break it down:

    Persistent Memory: Unlike regular variables that forget everything when the function ends, our static buffer remembers its contents between function calls. It's like having a notepad that doesn't get erased when you close the book!

    Picking Up Where We Left Off: Thanks to this memory, we can continue reading from exactly where we stopped last time. No need to start from the beginning of the file each time get_next_line is called.

    Handling Partial Reads: Sometimes, we might read more than one line into our buffer. The static variable allows us to keep that extra data for the next function call, ensuring we don't lose any information.

How It Works in get_next_line

A typical lifecycle of our static buffer:

    First Call:
        We allocate memory for buffer and read from the file.
        We extract the first line and return it.
        Any leftover data stays in buffer.

    Subsequent Calls:
        buffer still contains the leftover data from last time.
        We start by checking if there's a complete line in buffer.
        If not, we read more from the file and append to buffer.
        We extract the next line and update buffer again.

    Last Call:
        We've reached the end of the file.
        We return any remaining data in buffer.
        We free buffer and set it to NULL.

Why Static?

    Efficiency: We don't need to re-read the entire file for each line. We just continue from where we left off.
    Simplicity: The static variable handles the state management for us. No need to pass around a pointer to keep track of our position.
    Memory Management: We can allocate memory once and reuse it, rather than allocating new memory for each function call.

The Catch

While our static buffer is very useful, it does come with a few quirks:

    ⚠️ Multiple File Descriptors: If you're reading from multiple files, you'll need to handle each file descriptor separately.
    ⚠️ Memory Usage: The buffer sticks around until the program ends, even if you're done reading the file.
    ⚠️ Thread Safety: If you're working in a multi-threaded environment, you'll need extra care to make this thread-safe.

How that works?

    Buffer, Our Old Friend: Just like in our buffer overflow example, get_next_line uses a buffer. But don't worry, it's not trying to overflow anything! This buffer is more like a temporary storage space.
    Reading Chunks: Instead of reading the whole file at once, it reads chunks into the buffer. Think of it like taking bites of a sandwich instead of shoving the whole thing in your mouth.
    Searching for the Newline: After each read, it looks for the \n character. It's like playing "Where's Waldo?", but Waldo is a newline, and the crowd is our buffer full of characters.
    Returning the Line: When it finds a newline (or reaches the end of the file), it says "Aha! Here's a complete line!" and returns it to you.
    Remembering Where It Left Off: Here's where it gets clever. It remembers where it stopped, so the next time you call it, it starts from there. It's like using a bookmark in a really long book.
    
<h2>Why is <fcntl.h> important in get_next_line?</h2>

In the get_next_line project, <fcntl.h> is typically included because it provides file Access Modes: Constants like O_RDONLY (read-only), O_WRONLY (write-only), and O_RDWR (read and write).


How does it work in get_next_line?

In get_next_line, the open() function (declared in <fcntl.h>) is commonly used to open a file and obtain its file descriptor (fd). This fd is then passed to get_next_line() to read the file line by line.

#include <fcntl.h> is essential for:

- Defining constants like O_RDONLY, O_WRONLY, O_CREAT, etc.
- Using system-level file manipulation functions like open().

Without it, your program wouldn’t compile if you’re using open() or similar low-level file operations.


<h1>Resources</h1>

https://www.gnu.org/software/libc/manual/html_node/Processes.html#:~:text=A%20process%20executes%20a%20program,independently%20of%20the%20other%20copies.&text=The%20processes%20created%20by%20a%20given%20parent%20are%20called%20its%20child%20processes.
https://www.geeksforgeeks.org/memory-layout-of-c-program/
https://stackoverflow.com/questions/14042824/where-is-open-max-defined-for-linux-systems
https://www.geeksforgeeks.org/what-is-memory-leak-how-can-we-avoid/
https://man7.org/linux/man-pages/man2/open.2.html
https://prezi.com/4mhun2mlbssd/get-next-line/
https://www.ibm.com/docs/en/xl-c-and-cpp-linux/16.1.0?topic=iod--1
https://www.tutorialspoint.com/cprogramming/c_preprocessors.htm
https://jameshfisher.com/2017/02/22/ssize_t/
https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
https://velog.io/@ljiwoo59/getnextline
https://www.educative.io/answers/what-is-a-buffer-in-c
https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
https://www.educba.com/macros-in-c/

