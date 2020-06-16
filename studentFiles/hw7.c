/**************************************************************************
  Student frame work.   Add and remove as you see fit.
  
  07/14/2017    R. Repka    Initial release
 * ***********************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"
#define REPEAT_NUM (200000)
/************************************************************************
  Tests three types of root finding, secant, newton, and bisection,
  based on user input and prints out the timing results.
************************************************************************/
int main(int argc, char* argv[])
{
   /*------------------------------------------------------------------------
      UI variables with sentential values
   ------------------------------------------------------------------------*/
   int verbose = 0;
   enum modes {UNDEF, BISECT, SECANT, NEWTON} mode = UNDEF;
   double tol = 0.0;
   double guess1 = INFINITY;   
   double guess2 = INFINITY;

   /*------------------------------------------------------------------------
     These variables are used to control the getopt_long_only command line 
     parsing utility.  
   ------------------------------------------------------------------------*/
   int rc;
   /* getopt_long stores the option index here. */
   int option_index = 0;
  
   /* This contains the short command line parameters list */
   char *getoptOptions = "v";    /* add lots of stuff here */
  
   /* This contains the long command line parameter list, it should mostly 
     match the short list                                                  */
   struct option long_options[] = {
      /* These options don’t set a flag.
         We distinguish them by their indices. */
      {"verbose",   no_argument,       0, 'v'},
      {"verb",      no_argument,       0, 'v'},
      {"v",      no_argument,       0, 'v'},
      {"bisection",      no_argument,       0, 'b'},
      {"b",      no_argument,       0, 'b'},
      {"secant",      no_argument,       0, 's'},
      {"s",      no_argument,       0, 's'},
      {"newton",      no_argument,       0, 'n'},
      {"n",      no_argument,       0, 'n'},
      {"tolerance",      required_argument,       0, 't'},
      {"tol",      required_argument,       0, 't'},
      {"t",      required_argument,       0, 't'},
      {"guessa",      required_argument,       0, 'g'},
      {"ga",      required_argument,       0, 'g'},
      {"g",      required_argument,       0, 'g'},
      {"bracket_a",      required_argument,       0, 'g'},
      {"ba",      required_argument,       0, 'g'},
      {"guessb",      required_argument,       0, 'u'},
      {"gb",      required_argument,       0, 'u'},
      {"bracket_b",      required_argument,       0, 'u'},      
      {"bb",      required_argument,       0, 'u'},      
      {"u",      required_argument,       0, 'u'},      
      {0, 0, 0, 0}
   };
  
   opterr = 1;           /* Enable automatic error reporting */
   while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options, 
                                                    &option_index)) != -1) { 
 //     printf("getopt_long_only() returned ='%c' index = '%d'\n",  rc, option_index);   
      /* Detect the end of the options. */
      switch (rc)
        {
        case 'v':                    /* Verbose */
          verbose = 1;
          break;

	case 'b':
	   mode = BISECT;
	   break;

	case 's':
	   mode = SECANT;
	   break;

	case 'n':
	   mode = NEWTON;
	   break;

	case 't':
	   tol = atof(optarg);
	   break; 

	case 'g':
	   guess1 = atof(optarg);
	   break;

	case 'u':
	   guess2 = atof(optarg);
	   break; 

        case '?':  /* Handled by the default error handler */
          break;

       default:
          printf ("Internal error: undefined option %0xX\n", rc);
          exit(PGM_INTERNAL_ERROR);
       } // End switch 
   } /* end while */

   /*------------------------------------------------------------------------
     Check for command line syntax errors
   ------------------------------------------------------------------------*/
   if ((optind < argc) /* add lots of stuff here */  ){
      fprintf(stderr, "Tests root finding methods\n");
      fprintf(stderr, "usage: hw5 -b[isection] | -s[ecant] | -n[ewton]   -t[ol[erance} number\n");
      fprintf(stderr, "          -g[uess1] number   <-g[u]ess2 number   <-verb[ose]> \n");
      fprintf(stderr, " e.g:   hw5 -bisection -tol 1E-6 -g1 -2 -g2 3 -verb\n"); 
      fflush(stderr);
      return(PGM_INTERNAL_ERROR);
   } /* End if error */

   /* Performs the root finding with bisection */
   if(mode == BISECT)
   {
DECLARE_TIMER(BTIMER)
START_TIMER(BTIMER)
DECLARE_REPEAT_VAR(V)
BEGIN_REPEAT_TIMING(REPEAT_NUM, V)
     bisection(&func1, guess1, guess2, tol, verbose); 
END_REPEAT_TIMING
PRINT_TIMER(BTIMER)
PRINT_RTIMER(BTIMER, REPEAT_NUM)
   }  // End if bisection
   
   /* Performs the root finding using the secant method */
   else if(mode == SECANT)
   {
DECLARE_TIMER(STIMER)
START_TIMER(STIMER)
DECLARE_REPEAT_VAR(V)
BEGIN_REPEAT_TIMING(REPEAT_NUM, V)
     secant(&func1, guess1, guess2, 1000, tol, verbose);
END_REPEAT_TIMING
PRINT_TIMER(STIMER)
PRINT_RTIMER(STIMER, REPEAT_NUM)
   } // End secant
   
   /* Performs the root finding using newtons method */
   else /* must be newton */
   {
DECLARE_TIMER(NTIMER)
START_TIMER(NTIMER)
DECLARE_REPEAT_VAR(V)
BEGIN_REPEAT_TIMING(REPEAT_NUM, V)
     newton(&func1, &func1Deriv, guess1, 1000, tol, verbose);
END_REPEAT_TIMING
PRINT_TIMER(NTIMER)
PRINT_RTIMER(NTIMER, REPEAT_NUM)
   } // End newton 
   
    return PGM_SUCCESS;
}
