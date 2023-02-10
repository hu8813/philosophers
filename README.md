#The dining philosophers problem is an example of synchronization and deadlock avoidance. 

The solution to the dining philosophers problem is to use a lock (or mutex) to coordinate the actions of the philosophers. 

The idea is that each philosopher must lock the fork to their left (or right) before they lock the fork to their right (left). To choose left or right is depended on the Number(id) % 2, meaning the 1st philoshoper will lock first left then right fork, the 2nd philosopher will do the opposite and so on.
 
This ensures that there is always at least one fork available to each philosopher and avoids deadlocks.

##Threads and Mutex
This project makes use of threads and mutexes to coordinate the actions of the philosophers. A thread is a separate execution path that runs simultaneously with other threads in the same process. In this project, each philosopher is implemented as a separate thread.

A mutex (short for "mutual exclusion") is a synchronization mechanism that allows multiple threads to share a resource (such as a fork) while avoiding deadlocks. In this project, the mutex is used to coordinate the actions of the philosophers, ensuring that each philosopher locks the fork to their left before they lock the fork to their right.
