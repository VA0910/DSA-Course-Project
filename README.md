# DSA-Course-Project
This repository includes a course project from my DSA lab course. It is to create an E-rickshaw transportation system for my college.
The Project : E-Rickshaw Transportation in IITG campus
The vision : To assign the nearest e-rickshaws to the passengers


Data Structure Used : Graphs with Priority Queue
Reason : To assign each location as nodes and the passenger and e-rickshaws are traversing them in the minimum route distance. 
Using Dijkstra’s algorithm we can find the shortest path. 

What does it do?
The program assigns each passenger to the nearest e-rickshaw with space. On doing this it increments the load of the e rickshaw and also updates it’s route.
The routes signifies the nodes which are yet to be visited by the e-rickshaw
If the next node in the route is the same as some passenger’s drop node, it drops the passenger there. Also it decrements the load of the rickshaw.


This way it assigns the passengers the e-rickshaws and also e-rickshaws to the passengers.






