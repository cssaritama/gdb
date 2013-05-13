/* This testcase is part of GDB, the GNU debugger.

   Copyright 2013 Free Software Foundation, Inc.

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

/* Note: 'volatile' is used to make sure the compiler doesn't fold /
   optimize out the arithmetic that uses the variables.  */

static int
func1 (int a, int b)
{
  volatile int r = a * b;

  r += (a | b);
  r += (a - b);

  return r;
}

int
main(void)
{
  volatile int a = 0;
  volatile int b = 1;
  volatile int c = 2;
  volatile int d = 3;
  volatile int e = 4;
  volatile double d1 = 1.0;
  volatile double d2 = 2.0;

  /* A macro uses to build source lines that compile to a number of
     instructions, with no branches.  */
#define MULTIPLE_INSTRUCTIONS \
  do { a = b + c + d * e - a; } while (0)

  /* A line of source code that will be compiled to a number of
     instructions.  */
  MULTIPLE_INSTRUCTIONS; /* location 1 */

  /* A line of source code that compiles to a function call (jump or
     branch), surrounded by instructions before and after.  IOW, this
     will generate approximately the following pseudo-instructions:

addr1:
     insn1;
     insn2;
     ...
     call func1;
     ...
     insn3;
addr2:
     insn4;
*/
  e = 10 + func1 (a + b, c * d); /* location 2 */

  e = 10 + func1 (a + b, c * d);

  /* Generate a range that includes a loop in it.  */
#define RANGE_WITH_LOOP	\
  do								\
    {								\
      for (a = 0, e = 0; a < 15; a++)				\
	e += a;							\
    } while (0)

  RANGE_WITH_LOOP;

  RANGE_WITH_LOOP;

  /* Generate a range that includes a time-consuming loop.  GDB breaks
     the loop early by clearing variable 'c'.  */
#define RANGE_WITH_TIME_CONSUMING_LOOP					\
  do									\
    {									\
      for (c = 1, a = 0; a < 65535 && c; a++)				\
	for (b = 0; b < 65535 && c; b++)				\
	  {								\
	    d1 = d2 * a / b;						\
	    d2 = d1 * a;						\
	  }								\
    } while (0)

  RANGE_WITH_TIME_CONSUMING_LOOP;

  /* Some multi-instruction lines for software watchpoint tests.  */
  MULTIPLE_INSTRUCTIONS;
  MULTIPLE_INSTRUCTIONS; /* soft-watch */
  MULTIPLE_INSTRUCTIONS;

  return 0;
}
