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
    
