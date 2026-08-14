# Rational Approximation
#
# What this file does:
# Finds a good fraction p/q approximating a target under denominator constraints.
#
# Typical problem to recognize:
# A convergent of a continued fraction is an especially good rational approximation.
#
# Complexity / constraints:
# Useful when a decimal/real value must be represented by a small exact fraction.
#
# Main variables:
# x = target; p/q = candidate fraction; q = denominator bound.
#
# Variable guide for names used in this implementation:
# No unusual variable names detected; see the function signatures below.
#
# How to use:
# 1) Copy the needed function(s) into your template.
# 2) Match the parameter order with the function signature below.
# 3) Check the modulus / indexing assumptions before using it.
# 4) Keep the helper functions it depends on.
#

from fractions import Fraction
x = 3232.45622121
# gets the closest rational number to x where denominator is limited
p = Fraction(x).limit_denominator(2323)
print(p)
