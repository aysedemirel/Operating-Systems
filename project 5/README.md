# Libraries:
<stdio.h>     : c library </br>
<sys/wait.h>  : for wait </br>
<sys/types.h> : for pid_t </br>
<unistd.h>    : fork,pipe,I/O(read,write) </br>
<stdlib.h>    : for exit </br>


fd1 : using for first pipe </br>
fd2 : using for second pipe </br>
p   : using when fork </br>

The pipes are created. Controls are performed. Pipe fails when it is equal to -1. After the pipelines are created, the fork is created. The Fork must return a number greater than or equal to zero. If not, the fork fails. Fork enters the first parent (p> 0).

# In Parent
First, the first pipe has finished reading with close.To get data from the user, we defined the variables and received the value from the user. Parent wrote this value to the write part of the first pipe and turned off typing. At this point we need the child to take this value and turn it over and send it at the parent. For this, the parent begins to wait for the child.


# In Child
The write portion of the first pipe is closed. Because the first pipe will now be used for reading and the second pipe will be used for writing and flow from child to parent. Variables were determined for this purpose and the value of the first pipe was read. The change we made on this variable was to reverse the received value. Therefore we divide the value we read into decimal and create a new number in a variable.

#Example: 

Input: 123 </br> 
        --->123%10=3 newNum=0*10+3=3 num=123/10=12 </br>
        --->12%10=2  newNum=3*10+2=32 num=12/10=1 </br>
        --->1%10=1   newNum=32*10+1=321 num=1/10=0 --->num equals zero and the loop finished. </br>

The read part of the first and second pipes is closed. By writing to the second pipe, we aim to enable the parent to see the value of the child. In the second pipe, write is closed and the exit is done. We're going back to parent again. (going back after wait part)

   
# Back to Parent:

The write portion of the second pipe is closed. The value of the second pipe is read and assigned to the variable. Print is performed.For Second pipe, read part is also closed.

![image](https://github.com/aysedemirel/Operating-Systems/blob/master/project%205/img/1.png)
![image](https://github.com/aysedemirel/Operating-Systems/blob/master/project%205/img/2.png)

