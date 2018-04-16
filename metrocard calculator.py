balance = float(input("Please enter your metrocard balance: $"))

rides = int(balance // 2.75)
remainder = balance % 2.75
add = 2.75 - remainder #amount of ADDitional money need to spend to get a zero balance.

newbalance = balance + add #the new balance after adding the additional money
newrides = int(newbalance / 2.75) #the amount of rides newbalance gives.

newadd = 10.48 + add/1.05 #10.48 is the minimum needed to be spent to get a zero balance.

finalbalance = (newadd*1.05) + balance
noremainder = (finalbalance - int(finalbalance))

if noremainder > 0.001: #This helps round the numbers
    finalbalance = str(finalbalance)
    finalbalance = finalbalance[0:5]
    finalbalance = float(finalbalance)
    
finalride = finalbalance / 2.75

                    
print("At $2.75 per ride, your balance of", balance, "will give you", rides,'rides with a remaining balance of $',remainder)
print("You will need to spend an additional $",add, "to get a zero balance which would give you a new total of", newrides, "rides.")
print("However, to get the most out of your money, it is better to spend $5.5 or more to get the 5% bonus.")
print("To take advantage of the 5% bonus, you would need to spend an additional $", newadd,".")
print("This would give you a balance of $", finalbalance, "which gives", finalride, "rides.")
