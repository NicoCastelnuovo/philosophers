# philosophers

philosophers is a project developed for 42 Heilbroon School.

## Keywords
C programming - threads - mutex - spaghetti - survive please - concurrency - synchronization - Dijkstra

## Subject
Have you ever heard about the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)? If not, I have a suggestion for you: when you invite guests at home for dinner, be sure that you have enough cutlery for them!

## Explanation
The project covers the following topics:

### 0. The dining philosophers problem
From Wikipedia:

> Five philosophers dine together at the same table. Each philosopher has his own plate at the table. There is a fork between each plate. The dish served is a kind of spaghetti which has to be eaten with two forks. Each philosopher can only alternately think and eat. Moreover, a philosopher can only eat his spaghetti when he has both a left and right fork. Thus two forks will only be available when his two nearest neighbors are thinking, not eating. After an individual philosopher finishes eating, he will put down both forks.

The goal is then implement a concurrent algorithm which let every philosopher to survive.

### 1. Multithread programming
A _thread_ is an indipendent path of execution of a process, which can run concurrently with other threads of the same process. Unlike forked processes, the thread are part of the same process and share the same resources. Every thread can then consequently access the shared data, which brings up the _data race_ problem.

### 2. Data race
Threads part of the same process could race to access the shared data, but we want that every thread actually accesses this data one-by-one. We don't want that the same shared data is _used_ (which means read *AND* write) by multiple threads at the same time.

### 3. Race conditions
A race condition is not the same as Data race. From Wikipedia

> A race condition can arise in software when a computer program has multiple code paths that are executing at the same time. If the multiple code paths take a different amount of time than expected, they can finish in a different order than expected, which can cause software bugs due to unanticipated behavior.

### 4. Mutex && synchronization
Mutexes and synchronization come help us to get rid of these problem. Mutex means mutual exclusion: is a synchronization mechanism which ensure that only one thread at a time can access a shared resource.

### 5. Leaks free
Like in any other project of 42, the memory allocated by `malloc()` has to be properly freed. No leaks are tolerated. For this project I used `valgrind` to check the memory. At the beginning of the project was vital to think about how to handle this feature so that no child process leaks the memory. That because, the `t_pipe` structure hold everything, and the parent process has the job to free the memory at the end of the programm.

---

## Try it out
1. Clone the repository:
```
git clone https://github.com/ncasteln/42-philosophers
cd 42-philosophers
make
```
2. Run the program with the following arguments:
- Number of philosophers sit around the table, from 1 to 200 (5).
- Time to die: the time a philo can resist before die (800).
- Time to eat: the time a philo needs to eat its plate of spaghetti, which would be the time he holds the forks (200).
- Time to sleep: the time a philo needs to sleep (100).

```
./philo 800 200 100 5
```
3. Enjoy if no one dies, otherwise the next time remember to give them enough forks!
