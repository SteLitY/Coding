#I realized that things like .split("") and int() in python are just functions.
#This is my attempt of reproducing functions already in python. 
#My reproduced functions will be renamed to repeat the last letter of python's function.
#For an example: split("") will be splitt("")

def intt(v):
    #This function gets the int() of an integer.
    v = str(v)
    v = v.split(".")
    result = float(v[0]) #Float is used to remove the string and allow the number to compute math. It also gives an error when a letter/symbol is used.
    return result

def abss(a):
    #This function takes the absolute value of a number. Inspired by Ruby's .abs, but I just realized python has abs() too.
    if a <= 0:
        a = a * -1
    return a

def lenn(a): 
    #This function finds the length of a string.
    #If  you're using a string, be sure to use quotations
    #Alternatively, I can use a "for loop" to check if the ord of each index is greater than 0 and then add it to length.
    length = 0
    a = str(a) #This function only works when converted to a string.
    for i in a:
        length = length + 1
    return length

def prime(n):
    #This function checks to see if a number is prime by listing all the multiples of a number
    #and checking to see if it has more than 2 multiples.
    n = int(n) #converts it to a positive number
    multiple = []
    for i in range(n):
        i = i + 1 #module 0 gives an error
        if (n % i) == 0:
            multiple.append(i) #adds the multiples of a number to the list of multiples
    if n == 0 or n == 1:
        return ("1 and 0 are neither prime nor composite")
    elif n < 0:
        return ("Negative numbers are never prime!")
    elif len(multiple) > 2:
        return ("Not Prime. The multiples are: ", multiple)
    else:
        return ("Prime")
    
