/*---------------------------------------------------------------------------
  05/08/2017    R. Repka    Make derivative clearer
---------------------------------------------------------------------------*/
#include <math.h>

/*---------------------------------------------------------------------------
  Student framework equations to be solved to help with the root finder 
---------------------------------------------------------------------------*/
#include "rootfinding.h"

/*---------------------------------------------------------------------------
  This function implements the equation to be solved.  
  
  Where: double x - the value to evaluate
  Returns: double - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
double func1(double x){
 return 0.76 * x * sin((30.0/52.0)*x) * tan((10.0/47.0)*x) + 2.9 * cos(x+2.5) * sin(0.39*(1.5+x));
}


/*---------------------------------------------------------------------------
  This function implements the first derivative equation, which is calculated
  via any off-line process you wish (e.g  Wolfram Alpha)
  There is NO requirement to programmatically generate the derivative.
  
  Where: double x - the value to evaluate
  Returns: double - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
double func1Deriv(double x){

return -2.9*sin(.39*(x+1.5))*sin(x+2.5)+.76*sin((15.0*x)/26.0)*tan((10.0*x)/47.0)+.438462*x*cos((15.0*x)/26.0)*
tan((10.0*x)/47.0)+.161702*x*sin((15.0*x)/26.0)*(1.0/(cos((10.0*x)/47.0)))*(1.0/(cos((10.0*x)/47.0)))+1.131*cos(.39*(x+1.5))*
cos(x+2.5);  
}
