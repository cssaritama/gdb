/* This testcase is part of GDB, the GNU debugger.

   Copyright 2009-2014 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

unsigned int args[1];

pthread_barrier_t barrier;
pthread_t child_thread;

void *
child_function (void *arg)
{
  int my_number =  (long) arg;
  volatile int *myp = (int *) &args[my_number];

  pthread_barrier_wait (&barrier);

  while (*myp > 0)
    {
      (*myp) ++;

      asm ("	nop"); /* set breakpoint child here */
      asm ("	nop"); /* set breakpoint step-over here */
      usleep (1);
    }

  pthread_exit (NULL);
}


int
main ()
{
  int res;
  long i;

  pthread_barrier_init (&barrier, NULL, 2);

  i = 0;
  args[i] = 1;
  res = pthread_create (&child_thread,
			NULL, child_function, (void *) i);
  pthread_barrier_wait (&barrier);
  pthread_join (child_thread, NULL); /* set wait-thread breakpoint here */

  exit(EXIT_SUCCESS);
}
