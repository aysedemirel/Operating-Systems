# In main function:
# Variables:
--threadNumber -> number of thread (Taking from console) </br>
--start -> start line </br>
--numlines -> document’s line </br>
--resultThread -> to print the return value from thread in main </br>
--td[] -> There is a thread array to create multiple threads. And the array is struct structure. The
structure has two variables: startline, readline. The startline variable is used to indicate start reading
line for each thread. Readline is used to return the line value from thread to the main function.

   Firstly, the line number is counted by using countLine() function. Then thread number is taken from
the command line. We need to calculate threadLine(it is a global variable and its type is float).
ThreadLine is using to divide lines for each thread.When line number is divided by thread number,
sometimes it will be a float, and the float number should round up. So ceil() function was used for
the purpose. For example, the document is 30 lines, and the thread number is 4. So threadLine =
ceil(30/4=7,5)=8.
   
   The second step is that create a thread and take the line parameter and print it. For loop is using for
the purpose. The loop will turn 0-thread number. In the loop:
   Firstly, the thread is created with pthread_create. If there are a failure, the program will show a
message when it was checking rc value. If there is no error, the thread will be created and the thread
function will work.With pthread_join, the thread will wait for others.And when the thread function
returns a value, it will help to assign a value to the readline variable.The format: "x. thread reads y
lines.". The line is printed with the format. Lastly, with if-else statement controls "start" variable
will increase.There are three conditions: First one is controlling that the normal state.For example,
threadLine is 4 and the document's line is 21.Sequentially start variable's value will be
0,4,8,12,16,20. When the value is 24, the second condition will happen. The second condition is
controlling: there are more lines to read but there is not enough place for threadLine to read. In the
example, the thread reads 1 line and the document finishes.The third condition is controlling: there
is no thread to read but if there is a thread.

# In countLine function:
With ifstream, the txt document is opened. In while loop, the line number will be increased until
the document ends.

# In threadFunc function(Thread Function):
With ifstream, the txt document is opened.The new document will be created by ofstream with
the format "startline.txt". When the thread reads none line, the text file will be created and its name
will be increased one by one. And the file will be empty. Here, patch is using that convert int to
string.In for loop, the lines will be printed in the new file according to start and end constraints.And
also read line will be counted. After the loop, the value will assign in struct's readline variable.The
thread will return struct variable to the main function.

![image](https://github.com/aysedemirel/Operating-Systems/blob/master/project%204/img/1.png)
![image](https://github.com/aysedemirel/Operating-Systems/blob/master/project%204/img/2.png)
![image](https://github.com/aysedemirel/Operating-Systems/blob/master/project%204/img/3.png)
![image](https://github.com/aysedemirel/Operating-Systems/blob/master/project%204/img/4.png)
