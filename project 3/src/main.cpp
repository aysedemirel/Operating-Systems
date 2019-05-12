#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

float threadLine;  //lines to read for each thread

pthread_mutex_t count_mutex;
ofstream output;

struct thread_data {
   int  startline;
   int  readline;
};

void *threadFunc(void *threadarg) {
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;

   int value = threadLine, line = 0;
   string s, var;
   ifstream f1;
   f1.open("input.txt");
   pthread_mutex_lock(&count_mutex);
   for(int j = 0; getline(f1, s); j++){
        if(j >= my_data->startline && j < (my_data->startline+value)){
          output << s << endl;
          line += 1;
        }
   }

   my_data->readline = line;
   pthread_mutex_unlock(&count_mutex);
   pthread_exit(my_data);
}

int countLine()
{
   ifstream f1;
   char c;
   int numlines = 0;

   f1.open("input.txt");

   f1.get(c);

   while (f1) {
        while (f1 && c != '\n') {
              f1.get(c);
        }
        numlines = numlines + 1;
        f1.get(c);
   }
   
   return numlines;
}

int main () {
   //ask thread number
   int threadNumber, rc, start=0, numlines;
   struct thread_data *resultThread;
   
   //count line number of input.txt
   numlines = countLine();

   cout << "number of thread ? : ";
   cin >> threadNumber;


   //create threads

   pthread_t threads[threadNumber];
   struct thread_data td[threadNumber];
   threadLine = ceil(numlines/(float)threadNumber);
   
   output.open("output.txt");
   
   for(int i = 0; i < threadNumber; i++ ) {
       
      td[i].startline = start;

      rc = pthread_create(&threads[i], NULL, threadFunc, (void *)&td[i]);

      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }

      if(start+threadLine <= numlines) start += threadLine;
      else if(start+threadLine > numlines && start != numlines) start+=(numlines-start);
      else start += 1;   
   }
   
   for(int i = 0; i < threadNumber; i++)
   {
      //print number of line for each thread
      pthread_join(threads[i],(void**)&resultThread);
      cout << i+1 << ".thread reads " << resultThread->readline << " lines." << endl;
   } 

   pthread_exit(NULL);
   output.close();
}




