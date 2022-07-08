EXEC = Project2

HEADERS = card.h deck.h SortedLinkedList.h rank.h pokerhand.h
#(listing all header files here, separated by space) 
OBJECTS = card.o deck.o SortedLinkedList.o rank.o pokerhand.o 
#(listing all of your object files here, separated by space)

#Runs default as PA2 with the header and objects
default: PA2.o $(HEADERS) $(OBJECTS)
	g++ $^ -o $(EXEC)


#Runs as testPA2 with header and objects
testPA2: testPA2.o $(HEADERS) $(OBJECTS) 	
	g++ $^ -o testPA2 


#cleans the object files
clean: 
	rm -i *.o $(EXEC) 

