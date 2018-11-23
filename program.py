def max(x,y):
   if x > y:
      return x
   else:
      return y
max(5,1)

def sum(x):
   if x == 0:
      return 0
   return x + sum(x-1)

sum(5)