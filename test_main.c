#include <sys/time.h>
#include "time_manager.h"
#include <stdio.h>

int get_time() {
  struct timeval tv;

  gettimeofday(&tv, NULL);

  unsigned long long time =
      (unsigned long long)(tv.tv_sec) * 1000 +
      (unsigned long long)(tv.tv_usec) / 1000;

  return time;
}

int main(){
  while(1){
    printf("%d\n", get_time());
  }
}
