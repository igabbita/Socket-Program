## Socket Programming Sample ##

The objective of this project is to write a socket program for 2 clients and a Server. Client 1 sends a structure comprising of an integer value, a floating value and a character value to the server process. The server changes each of the value in a way such that it doubles the integer, increments the float by 1 and increases the character value to the next higher character with a roll over. The server then prints the original values that it received as well as the modified values and then sends these values to Client 2 and then Client 2 displays these values.

###Server###
Execute the following commands

    > gcc -c sockServer.c 
    > gcc -o server sockServer.c –lsocket -lnsl
    > ./server  rohan.sdsu.edu [Port_No]
    
###Client 1###
Execute the following commands

    > gcc -c sockClient1.c 
    > gcc -o client1 sockClient1 –lsocket -lnsl 
    > ./client1 rohan.sdsu.edu [Port_No]
    
###Client 2###
Execute the following commands

    > gcc -c client2.c 
    > gcc -o client2 sockClient2.c 
    > ./client2 rohan.sdsu.edu [Port_No]

Order of Execution

1. Login & Run Server
2. Login and Run  Client 1 followed by Client 2




