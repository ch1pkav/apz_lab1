# Microservices basics

This is a very basic microservice architecture implementation in C++, comprised of three microservices

## Running in docker
This project can either be run directly on your machine, or in a docker container.

In the cloned project root, run:

```{bash}
docker compose up
```

This will run all the microservices in docker container, mapped onto othe localhost ports.

To test if it's working, you can run:

```{bash}
curl --request POST "0.0.0.0:18080/?message=Hello+microservices"; curl --request GET "0.0.0.0:18080"
```

You should get a UUID of your message from the logging service and a "Not implemented" message from the message service.

## Running locally
You can also run this architecture locally. For this, you need to install all the dependencies and compile the project manually.

### Dependencies

+ CMake, gcc, Boost, make
+ [libcpr](https://github.com/libcpr/cpr)
+ [crowcpp](https://crowcpp.org/master/) (Pulled in automatically via CMake)

### Compilation

In the project root directory:

```{bash}
./compile.sh
```
### Running

To run any of the microservices, execute the corresponding binary

```{bash}
./bin/apz_facade
./bin/apz_message
./bin/apz_logging
```

NOTE: You may need to run the following prior to executing the microservice binaries:

```{bash}
export LD_LIBRARY_PATH=$PWD/lib64
```
