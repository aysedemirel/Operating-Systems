# In main function:
# Variables:
--threadNumber -> number of thread (Taking from console)
--start -> start line
--numlines -> document’s line
--resultThread -> to print the return value from thread in main
--td[] -> There is a thread array to create multiple threads. And the array is struct structure. The
structure has two variables: startline, readline. The startline variable is used to indicate start reading
line for each thread. Readline is used to return the line value from thread to the main function.
    
   Firstly, the line number is counted by using countLine() function. Then thread number is taken
from the command line. We need to calculate threadLine(it is a global variable and its type is float).
ThreadLine is using to divide lines for each thread.When line number is divided by thread number,
sometimes it will be a float, and the float number should round up. So ceil() function was used for
the purpose. For example, the document is 30 lines, and the thread number is 4. So threadLine =
ceil(30/4=7,5)=8. Output variable is used to write the lines in output.txt. Output variable is global.
When output.open() is running, the output.txt will be created if there is no document. It will remain
open until output.close() is happened.

   The second step is that create a thread and take the line parameter and print it. For loop is using
for the purpose. The loop will turn 0-thread number. In the loop:

   Firstly, the thread is created with pthread_create. If there are a failure, the program will show a
message when it was checking rc value. If there is no error, the thread will be created and the thread
function will work. Lastly, with if-else statement controls "start" variable will increase.There are
three conditions: First one is controlling that the normal state.For example, threadLine is 4 and the
document's line is 21.Sequentially start variable's value will be 0,4,8,12,16,20. When the value is
24, the second condition will happen. The second condition is controlling: there are more lines to
read but there is not enough place for threadLine to read. In the example, the thread reads 1 line and
the document finishes.The third condition is controlling: there is no thread to read but if there is a
thread.

   Last step is that creating pthread_join.With pthread_join, the thread will wait for others.And
when the thread function returns a value, it will help to assign a value to the readline variable.The
format: "x. thread reads y lines.". The line is printed with the format.

# In countLine function:
With ifstream, the txt document is opened. In while loop, the line number will be increased until
the document ends.

# In threadFunc function(Thread Function):
With ifstream, the txt document is opened.After open input.txt, mutex will start work. When a
thread is in the output file, other threads will wait it because of mutex. In for loop, sequentially the
lines will be printed in the output file according to start and end constraints. Output file’s context
can be mixed. For example, second thread can start work before first thread. So second context will
be printed before first context. And also read line will be counted.After the loop, the value will
assign in struct's readline variable. And mutex will finish.So other threads can work on the output
document. The thread will return struct variable to the main function.
