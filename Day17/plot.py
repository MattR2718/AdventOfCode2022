import matplotlib.pyplot as plt
  
f = open("Day17/diffData.txt", 'r');
""" for l in f:
    print(l) """
x,y = [], []
for l in f:
    row = l.split(", ")
    #print(row[0])
    x.append(row[0])
    y.append(row[1].rstrip(row[1][-1]))
    #y.append(row[1])
  
for i in range(len(x)):
    print(x[i], y[i])

# plotting the points 
plt.plot(x, y)
  
# naming the x axis
plt.xlabel('x - axis')
# naming the y axis
plt.ylabel('y - axis')
  
# giving a title to my graph
plt.title('My first graph!')
  
# function to show the plot
plt.show()