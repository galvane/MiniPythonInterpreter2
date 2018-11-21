def max(x,y):
   if x > y:
      return x
   else:
      return y


def sum(x):
   if x == 0:
      return 0
   return x + sum(x-1)

sum(5)