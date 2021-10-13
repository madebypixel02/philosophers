# philosophers

*I’ve never thought philosophy would be so deadly 💀*

### Table of Contents
* [Introduction](#introduction)
	* [Dining Philosophers Problem](#dining-philosophers-problem)
* [My philo program](#my-philo-program)
	* [Parsing Data](#parsing-data)
	* [Threads and Mutexes](#threads-and-mutexes)
	* [Death Checking](#death-checking)
* [Roadblocks](#roadblocks)
	* [Deadlocks](#deadlocks)
	* [usleep](#usleep)
* [Installation](#installation)
* [Summary](#summary)

## Introduction

This project follows the trend we saw in the pipex project. However instead of using forks we use threads to run several tasks in parallel. Also, because of some properties of threads, using mutexes was needed

### Dining Philosophers Problem

The idea behind this problem comes from a very popular problem called *the dining philosophers problem*. It goes as follows. A certain number of philosophers sit on a round table. Each philosophers has a fork/chopstick on their left and their right. There are as many forks as philosophers on the table, and every philosopher has a bowl of spaghetti in front of them. Philosophers only do these tasks and in this specific order:

1) Grab fork from both their left and right sides (if they're available) 🍴
2) Start eating for ``X`` amount of time 🍝
3) Release both forks for other philosophers to use
4) Start thinking for ``X`` amount of time 🌙
5) Start thinking until forks are available to eat again 💭

Additionally, if a philosopher doesn't fetch both forks quickly enough, they will die 💀

The problem here is that philosophers must taks turns to grab forks, otherwise they might all get stuck with only one fork until they starve.


## My philo Program

We are asked to compile an executable called ``philo``, which will behave as follows:

```
usage: philo <philo_count> <die_time> <eat_time> <sleep_time> [<repeat_times>]
```

| Argument | Description | Details |
| :------: | :---------: | :-----: |
| ``philo_count`` | Number of philosophers | Larger than ``0`` |
| ``die_time`` | How often a philosopher must eat | At least ``0`` |
| ``eat_time`` | How long it takes for a philosopher to eat | At least ``0`` |
| ``sleep_time`` | How long it takes for a philosopher to sleep | At least ``0`` |
| ``repeat_times`` | How long it takes for a philosopher to eat | Larger than ``0`` (optional) |

Note: times are measured in milliseconds

### Parsing Data

I initially parse the above arguments and store them in a ``t_philo_data`` struct. I then create a linked list where every node is of type ``t_philo``. Every philosopher has their ``id``, their personal ``thread_id`` from their thread, the time of their last meal, and a pointer to the data we stored before. This linked list is cyclic, meaning the last node points to the head of the list.

### Threads and Mutexes

As mentioned before, this project uses both threads and mutexes. Threads allow for a single process to execute multiple tasks in parallel, sharing the memory between threads. Because some of our variables can be accessed/modified in the threads from a philosopher or from outside those threads, we need to use ``mutex``. It stands for mutual exclusion and prevents two threads from accessing a part of your code. If you need to modify a variable in one thread and read its variable in another one you must lock and unlock the access and modification of such variable so that you guarantee that you are not reading the variable's value right when it's being modified.

### Death Checking

In order to check when a philosopher is dead we must constantly check if the ``curent_time - last_meal_time >= die_time``. We must do this outside the philosophers' threads since inside them there are some delays due to the time it takes philosophers to eat or sleep. Right after launching all threads I run a function that endlessly monitors the philosophers to see if the above conditions are met. When this happens some mutexes prevent future actions from happening and the death message is displayed. Lastly all threads end and are received outside with ``pthread_join``.

## Roadblocks

Thoughout the project, there were some problems that did not have a trivial workaround, here are a few of them

### Deadlocks

One major problem we must solve is ``race conditions`` that lead to what is known as a ``deadlock``. In the philosophers problem this happens when every philosopher manages to grab one of their forks. In this case all forks will become unavailable yet no philosopher will eat since none of them has two forks. This will make it so that all philosophers will be idle till one of them dies.

My solution to this issue is that philosophers with an even ``id`` will wait 1 ms before trying to pick up forks, ehre as philosophers with an odd ``id`` need not wait.

### usleep

When a philosopher is eating or sleeping the philosopher's thread must wait a set amount of time in milliseconds. We are given the ``usleep`` function to use, but according to the manuals it will wait at least ``X`` *microseconds*, but the exact wait time is not predictable. For this reason I made my own ``ft_usleep`` which waits small chunks of microseconds until yoou've waited a total of ``X`` *milliseconds*.

## Installation

The subject for this project asked that we uploaded all our files inside a folder called ``philo/``. Inside there is a *Makefile* that compiles the source files inside the ``src/`` and ``src_lft/`` folders, to make object files inside the ``obj/`` and ``obj_lft/`` folders, as well as creating the executable ``philo`` inside the ``bin/`` folder

* Cloning the repository

```shell
git clone https://github.com/madebypixel02/philosophers.git
cd philosophers/philo
make
```

* Basic usage

```
make			compiles philo program
make norminette		runs norminette on all source files
```

* Examples

## Summary

Coming from my previous project, this project was done without too many issues. Would have been nice to do the bonuses but I thought it was not that meaningful. Minishell here I come!

October 13th, 2021
