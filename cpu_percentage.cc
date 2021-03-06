#include <time.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

int measure_usec_diff(struct timeval* t1, struct timeval* t2)
{
   int ts1, ts2;

   ts1 = t1->tv_sec * 1000000 + t1->tv_usec;
   ts2 = t2->tv_sec * 1000000 + t2->tv_usec;
   
   return ts2-ts1;

}

int calc_effective_sleep_time(int time_diff, int percentage)
{
  float sleep =  time_diff * (100.0/percentage - 1); 
  return sleep;
}


void make_it_sleep(int sleep_time)
{
    usleep(sleep_time); 
}

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++) {
         if (isdigit(s[i]) == false) {
              return false; 
         }
         else {
              return true; 
         }    
    } 
}

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf("Usage: ./cpu_percentage <percentage> ");
          return -1;
    }

    if (isNumber(argv[1]))
    {
        string user_defined_percentage = argv[1];  
        int percentage = stoi(user_defined_percentage);

        float time_diff; 
        struct timeval tval1, tval2;
        float t1, t2; 
        float TIME_DELAY_CONSTANT = 50000;
        while(1){
            gettimeofday(&tval1, NULL);
            while(1){
                gettimeofday(&tval2, NULL);
                time_diff = measure_usec_diff(&tval1, &tval2);

                if(time_diff > TIME_DELAY_CONSTANT)
                    break;
                }

            float sleep_time = calc_effective_sleep_time(time_diff, percentage);
            make_it_sleep(sleep_time);
        }
        
    }
    else
    {
        printf("This is an error because you didn't enter a number ");
    }
   
}

