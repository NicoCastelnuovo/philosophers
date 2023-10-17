# philosophers

philosophers is a project developed for 42 Heilbroon School.

## Keywords
C programming - threads - mutex -

## Subject


## Explanation
The project covers the following topics:


### 0. The dining philosophers problem


### 1. Multithread programming


### 2. Data race


### 3. Mutex


### 4. time functions


### 5. Leaks free
Like in any other project of 42, the memory allocated by `malloc()` has to be properly freed. No leaks are tolerated. For this project I used `valgrind` to check the memory. At the beginning of the project was vital to think about how to handle this feature so that no child process leaks the memory. That because, the `t_pipe` structure hold everything, and the parent process has the job to free the memory at the end of the programm.

---

## Try it out
1. Clone the repository:
```
git clone git@github.com:NicoCastelnuovo/philosophers.git philosophers
```
2.
```

```
3.

4. Enjoy!

---

## Notes
