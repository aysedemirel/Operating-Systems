#include <stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe
 
    pid_t p;
 
    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
 
    p = fork();
 
    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }
 
    // Parent process
    else if (p > 0)
    {
        close(fd1[0]);  // Close reading end of first pipe
        long long int number;
        long long int lastnumber;
        printf("Please enter the number:");
        scanf("%lld",&number);

        write(fd1[1], &number,sizeof(number));
        close(fd1[1]);

        wait(NULL);
 
        close(fd2[1]); // Close writing end of second pipe

        read(fd2[0], &lastnumber,sizeof(lastnumber));
        printf("number:  %lld  \n",lastnumber);
        close(fd2[0]);
    }
 
    // child process
    else
    {
       close(fd1[1]);  // Close writing end of first pipe
       long long int num,remainder,reversedNumber;
       read(fd1[0], &num, sizeof(num));
   
       while(num != 0)
       {
            remainder = num%10;
            reversedNumber = reversedNumber*10 + remainder;
            num /= 10;
       }
       num=reversedNumber;
       close(fd1[0]);
       close(fd2[0]);
 
       // Write concatenated string and close writing end
       write(fd2[1], &num,  sizeof(num));
       close(fd2[1]);
 
       exit(0);
    }


   return 0;
}
