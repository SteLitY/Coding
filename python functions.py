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

def lenn(a): ## Why does this only work for integers?
    #This function finds the length of a string.
    #Alternatively, I can use a "for loop" to check if the ord of each index is greater than 0 and then add it to length.
    length = 0
    a = str(a) #This function only works when converted to a string.
    for i in a:
        length = length + 1
    return length

