The dining philosophers problem is an example of synchronization and deadlock avoidance. 

The solution to the dining philosophers problem is to use a lock (or mutex) to coordinate the actions of the philosophers. 

The idea is that each philosopher must lock the fork to their left (or right) before they lock the fork to their right (left). To choose left or right is depended on the Number(id) % 2, meaning the 1st philoshoper will lock first left then right fork, the 2nd philosopher will do the opposite and so on.
 
This ensures that there is always at least one fork available to each philosopher and avoids deadlocks.
