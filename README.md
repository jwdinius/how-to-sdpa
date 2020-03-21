# How-to SDPA with Cmake

_I have been frustrated in past attempts to get SDPA to play nicely with Cmake, so I'm sharing this stub so that others might not experience similar problems._

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
(container)$ cd ~/libexample
(container)$ mkdir build && cd build && cmake .. && make
```

## Run examples
_make sure to build first!_  See above section.

`example`s 1-4 can be run without command-line args passed:

```shell
(container)$ cd ~/libexample/build
(container)$ ./examplex  # "x" is number 1-4
```

`example`s 5-6 have required command-line args.  Here are some samples for calling these examples:

```shell
(container)$ cd ~/libexample/build
(container)$ ./example5 ../config/example1.dat{-s} result.txt ../config/param.sdpa  # {-s} is optional; output is written to "result.txt" in current(build) folder
(container)$ ./example6 ../config/example1.dat{-s} ../config/example1.ini{-s} ../config/param.sdpa  # {-s} is optional, but must be matched to both .dat and .ini
```

## Cleaning up
The container is launched with the `--rm` flag passed, so docker will automatically clean-up/delete this container when you `exit` out of it.
