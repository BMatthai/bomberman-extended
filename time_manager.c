#include <sys/time.h>
#include "time_manager.h"

int get_time() {
  struct timeval *restrict tp = NULL;
  void *restrict tzp = NULL;
  gettimeofday(tp, tzp);

  return 1;
}
