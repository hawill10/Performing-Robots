## 1. Your definition of the word "robot"
For this assignment, I defined robot as a moving machine that performs certain set of movements based on a precoded program. This was due to technical difficulties, but later, I hope to make robots that at least appear to be autonomous to even a slight degree, making decisions by iteself. 
## 2. Describe your process and include the process pictures
### - Idea
I started off to make a robot that goes forward when the light is green and stop when it's red. Since it was impossible to make the vehicle recognize the color of the light and decide to stop or go, I synchronized the vehicle and the light in order to give the sense that the vehicle is working based on the color of the light. 
### - Process
So, first, I connected two motor to the arduino and set the value of `analogWrite` to a right value so that the motor has enough power to spin with the wheels. 80 seemed enough.
![motors with wheels](/images/motor_with_wheels.jpg) ![first circuit](/images/first_iteration.jpg)
Then, I built a frame on top of it that looked triangular. However, the frame could not bear the weight of motors and the movement of the vehicle. The bottom part kept collapsing whenever the motor spun.
![initial frame](/images/initial_frame.jpg)
Therefore, I added supporting parts, attaching pieces that connect the upper part of the frame and the bottom. The cardboard was stiff enough to help support the weight of the motors. Finally, the frame did not collapse even after a number of movements.
![final vehicle](/images/final_vehicle.jpg)
## 3. Describe the story and how the movement sequence tells it
The story is a vehicle moving based on the color of the traffic light. It stops whenever the light is red and goes when it's blue. I thought it would be more interesting if the interval of the lights were different. 
## 4. [A link to the video](https://youtu.be/HxyfnpIqfb4 "project video")
## 5. Describe any difficulties you had and how you overcame them or worked around them
First, I had difficulties giving the sense that the vehicle was responding to traffic lights. I was thinking of putting the arduino into the robot so it looked complete. However, in order to synchronize the vehicle and the lights, I had to connect both to aruino, making it impossible to put the arduino inside the robot. As a work around, I made longer wires and built a frame that had holes where wire could go thorough so that the vehicle could move relatively freely with the arudino sitting outside it. 
Moreover, since I'm not used to building physical stuff, I  had difficulties building the frame that could handle the motors. I had expectations that did not work, so I had to add parts after each failure. In the end, the vehicle looked better than I imagined, but I learned the importance of additional parts that can support the weight of core components. 
