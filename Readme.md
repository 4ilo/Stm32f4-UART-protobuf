# Stm32F4 protobuf over UART example

- Stm32f4 microcontoller
- Libopencm3
- Google protobuf
- nanopb

## Stm32f4 server
```
make
make flash
```

## Python client
```
make -C proto
./cli.py
```

## C++ client
```
bazel build //client:client
```
