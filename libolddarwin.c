#ifdef CONFIG_OLDDARWIN
#ifdef __MACH__
#include <time.h>
#include <sys/time.h>
#include <mach/clock.h>
#include <mach/mach.h>

int clock_gettime (int, struct timespec *);

/* 0 (REALTIME_CLOCK=SYSTEM_CLOCK) or 1 (CALENDAR_CLOCK) */
int clock_gettime (int clk_id, struct timespec *ts) {
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), clk_id, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
  return 0;
}

#endif
#endif
