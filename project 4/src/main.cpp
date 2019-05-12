#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

float threadLine;  //lines to read for each thread

struct thread_data {
   int  startline;
   int  readline;
};

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

void *threadFunc(void *threadarg) {
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;

   int value = threadLine, line = 0;
   string s, var;
   ifstream f1;
   f1.open("input.txt");

   ofstream readinglines;
   var=patch::to_string(my_data->startline + 1) + ".txt";

   readinglines.open(var.c_str());

   for(int j = 0; getline(f1, s); j++){
        if(j >= my_data->startline && j < (my_data->startline+value)){
          readinglines << s << endl;
          line += 1;
        }
   }
   readinglines.close();
   my_data->readline = line;

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

   cout << "number of thread ? : ";
   cin >> threadNumber;
   //count line number of input.txt
   numlines = countLine();

   //create threads
   pthread_t threads[threadNumber];
   struct thread_data td[threadNumber];
   threadLine = ceil(numlines/(float)threadNumber);

   for(int i = 0; i < threadNumber; i++ ) {
       
      td[i].startline = start;

      rc = pthread_create(&threads[i], NULL, threadFunc, (void *)&td[i]);

      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
      //print number of line for each thread
      pthread_join(threads[i],(void**)&resultThread);
      cout << i+1 << ".thread reads " << resultThread->readline << " lines." << endl;

      if(start+threadLine <= numlines) start += threadLine;
      else if(start+threadLine > numlines && start != numlines) start+=(numlines-start);
      else start += 1;   
   }
   pthread_exit(NULL);
}
