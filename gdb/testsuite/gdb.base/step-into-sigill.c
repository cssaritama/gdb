#include <signal.h>
#include <unistd.h>

int pid;

#ifdef SIGILL
#  define HAVE_SIGILL 1
#else
#  define HAVE_SIGILL 0
#endif

#ifdef SIGEMT
#  define HAVE_SIGEMT 1
#else
#  define HAVE_SIGEMT 0
#endif

#ifdef SIGSEGV
#  define HAVE_SIGSEGV 1
#else
#  define HAVE_SIGSEGV 0
#endif

int have_SIGILL = HAVE_SIGILL;
int have_SIGEMT = HAVE_SIGEMT;
int have_SIGSEGV = HAVE_SIGSEGV;

/* Signal handlers, we set breakpoints in them to make sure that the
   signals really get delivered.  */

#ifdef SIGILL
void
handle_ILL (int sig)
{
}
#endif

#ifdef SIGEMT
void
handle_EMT (int sig)
{
}
#endif

#ifdef SIGSEGV
void
handle_SEGV (int sig)
{
}
#endif

void
done (void)
{
}

void
gen_SIGILL (void)
{
#ifdef SIGILL
  kill (pid, SIGILL);
#endif
  done ();
}

void
gen_SIGEMT (void)
{
#ifdef SIGEMT
  kill (pid, SIGEMT);
#endif
  done ();
}

void
gen_SIGSEGV (void)
{
#ifdef SIGSEGV
  kill (pid, SIGSEGV);
#endif
  done ();
}

int
main ()
{
  pid = getpid ();

#ifdef SIGILL
  signal (SIGILL, handle_ILL);
#endif
#ifdef SIGEMT
  signal (SIGEMT, handle_EMT);
#endif
#ifdef SIGSEGV
  signal (SIGSEGV, handle_SEGV);
#endif

  /* The test single steps many times until the signal is delivered.
     Call 'kill' once, to continue over it once, resolving PLTs, which
     would be slow to single-step over.  */
  kill (pid, 0);

  gen_SIGILL (); /* set breakpoint SIGILL here */

  gen_SIGEMT (); /* set breakpoint SIGEMT here */

  gen_SIGSEGV (); /* set breakpoint SIGSEGV here */

  return 0;
}
