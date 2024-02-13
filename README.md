# Microservices basics

This is a very basic microservice architecture implementation in C++, comprised of three microservices

## Dependencies

+ CMake, gcc, Boost, make
+ [libcpr](https://github.com/libcpr/cpr)
+ [crowcpp](https://crowcpp.org/master/) (Pulled in automatically via CMake)

## Compilation

In the root directory:

```{bash}
cmake -B build; cd build; make
```
## Running

To run any of the microservices, execute the corresponding binary

```{bash}
./apz_lab1_facade
./apz_lab1_message
./apz_lab1_logging
```
