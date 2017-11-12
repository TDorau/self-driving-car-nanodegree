### Reflection:



#### The Model.

The model includes equations for vehicle x and y, velocity v, orientation psi as well as cross track error(cte) and orientation error (epsi). Based on the previous equation the model calculates the current state using the state equations shown below.

![Model](./model.jpg)

Model output are mainly steer and throttle value.

#### Timestep Length and Elapsed Duration (N & dt).

size_t N = 10;
double dt = 0.1;

For a car at that speed more than a few seconds doesn't make sense. So I first tried N = 20 and dt = 0.1 (2s time). Results improved by lowering N first to 15 and even more to 10. So trying other values than shown in the walkthrough video didn't lead to improved model performance.

#### Polynomial Fitting and MPC Preprocessing

In main.cpp lines 103-109 a transformation is being done for vehicle x and y coordinates to be at 0.

#### Model Predictive Control with Latency

The state that is handed to the MPC.cpp Solver function is altered by incorporating the latency (main.cpp lines 132-142). So instead of the current state the solver uses the state that is a prediction at latency time.

Additionally I added a pentaly factor to the cost function(MPC.cpp line 70). This combination of delta and veloctiy adds a lot of smoothness, especially in curves. 
