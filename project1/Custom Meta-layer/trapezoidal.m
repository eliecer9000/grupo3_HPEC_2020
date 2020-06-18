# Course: MP-6171 High Performance Embedded Systems
# Tecnologico de Costa Rica (www.tec.ac.cr)
# Developers Name: eliecer@estudiantec.cr
# This script is structured in Octave (https://www.gnu.org/software/octave/)
# General purpose: Composite Trapezoidal Rule Prototyping
# Input: Lower value, upper value and sub-intervals
# Output: numerical approximation

# Based on http://www.maths.lth.se/na/courses/FMN050/media/material/lec14.pdf
function approximation = Trapezoidal(lower, upper, subInterval)
  if (subInterval <= 1)
    error("The number of intervals must be greater than zero");
  endif

  h = (upper - lower)/subInterval; # This is known as the step of the method
  f_l = f(lower);# This is the function value evaluated in the lower limit
  f_u = f(upper);# This is the function value evaluated in the upper limit
  sum = 0;       # This variable holds the sum of the function evaluated in all
                 # the points starting from lower up to upper - h, where n is
                 # the number of intervals we split the range in
  x = lower;     # This is x_0
  for i = 1:(subInterval - 1)
    x = x + h;   # As it keeps iterating, add the step
    sum = sum + f(x);
  endfor

  approximation = (h/2) * (f_l + f_u + 2 * sum);
endfunction

# This is the function to approximate for this specific problem.
# It can be changed to modify the integral of the function we are approximating
function retval = f(x)
  retval = 1/(1 + x^2);
endfunction