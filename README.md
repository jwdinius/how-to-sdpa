# How-to Setup Building Examples with Callable SDPA Library and Cmake

> Unfortunately, the architecture of SDPA is such that [`exit`](http://www.cplusplus.com/reference/cstdlib/exit/) syscall is required at end of each solve with the SDPA callable library to avoid nasty behavior (buffer overrun warning and segmentation fault), which means that the calling process will be stopped.  This makes the callable SDPA library useless for me; my desired use-case is to have a function call that solves an semidefinite relaxation problem using SDPA and then return the result of the optimizer to subsequent logic.  Alas, this does not appear to be possible so I am abandoning SDPA for my project.  I'm leaving the repo here for other's reference though.

_I have been frustrated in past attempts to get SDPA to play nicely with Cmake, so I'm sharing this stub so that others might not experience similar problems.  I took the_ `libexample` _folder that comes with the aptitude package_ `libsdpa-dev` _in Ubuntu Bionic 18.04 and created a CMake workflow to build the examples._

## Steps
* [Install Docker](https://docs.docker.com/install/)
* Build Docker image locally
* Launch Docker container
* Build examples
* Run examples
* Cleaning up

## Build Docker image locally
```shell
(host)$ cd {repo-root-dir}/docker
(host)$ ./build-docker.sh
```

## Launch Docker container
```shell
(host)$ cd {repo-root-dir}
(host)$ ./docker/run-docker.sh
```

## Build examples
```shell
(container)$ cd ~
(container)$ mkdir build && cd build && cmake .. && make
```

## Run examples
_make sure to build first!_  See above section.

`example`s 1-4 can be run without command-line args passed:

```shell
(container)$ cd ~/build
(container)$ ./examplex  # "x" is number 1-4
```

`example`s 5-6 have required command-line args.  Here are some samples for calling these examples:

```shell
(container)$ cd ~/build
(container)$ ./example5 ../config/example1.dat{-s} result.txt ../config/param.sdpa  # {-s} is optional; output is written to "result.txt" in current(build) folder
(container)$ ./example6 ../config/example1.dat{-s} ../config/example1.ini{-s} ../config/param.sdpa  # {-s} is optional, but must be matched to both .dat and .ini
```

## Cleaning up
The container is launched with the `--rm` flag passed, so docker will automatically clean-up/delete this container when you `exit` out of it.
