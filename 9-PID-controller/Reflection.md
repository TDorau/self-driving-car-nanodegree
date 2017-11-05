### Reflection:

#### Describe the effect each of the P, I, D components had in your implementation.

The proportional term, the control is set in proportion the the cte. Only using this term leads to a lot of overshooting as expected.
The derivative term considers the rate of change of error. This is to get rid of the overshooting problem. As expected by using this term steering is smoother than just using the P-controller.
The integral term gets larger when the error term is high for quite some time, therefore correcting systematic bias.

#### Describe how the final hyperparameters were chosen.

Final values: Kp = -0.3 Ki = -0.005 Kd = -10

http://smithcsrobot.weebly.com/uploads/6/0/9/5/60954939/pid_control_document.pdf

I used the manual tuning steps described in the link above. These are as follows:

1. Set Kp, Ki, and Kd to 0. This will disable them for now.
2. Increase Kp until the error is fairly small, but it still gets from the beginning to nearly
the end quickly enough.
3. Increase Kd until any overshoot you may have is fairly minimal. But be careful with
Kd – too much will make it overshoot.
4. Increase Ki until any error that is still existing is eliminated. Start with a really small
number for Ki, don't be surprised if it is as small as 0.0001 or even smaller.
5. Using the rules of tuning the constants (in the table on the previous page), you can
change around the constants a little bit to get it working to the best performance.

