
# Program to show various ways to read and 
# write data in a file. 
file1 = open("myfile.txt","w") 
L = ["This is Delhi \n","This is Paris \n","This is London \n"]  
  
# \n is placed to indicate EOL (End of Line) 
file1.write("Hello \n") 
file1.writelines(L) 
file1.close() #to change file access modes 
  
file1 = open("myfile.txt","r+")  
  
print ("Output of Read function is ")
print (file1.read())