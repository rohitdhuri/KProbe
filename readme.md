# CS550 - Operating Systems
Spring 2020  
State University of New York at Binghamton 

##Project Title  
Kernel module that takes the process-ID of an active process as an argument via the module parameter, and tracks all the virtual addresses on which the target process faults. It will print the virtual addresses to the system log using printk(). This works for any arbitrary target process.

###Usage
1. Compile the module using the provided makefile.
2. Then get the PID of the process you want to track.
3. Insert the module with a parameter named 'u_pid' as the process pid.
4. Look into the system log for pagefaults.
5. Remove the kernel module.

####Credits
Author: Rohit Mahendra Dhuri
Developed on Ubuntu 18.04.3 LTS


