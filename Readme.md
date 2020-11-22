# Stm32F4 protobuf over UART example

- Stm32f4 microcontoller
- Libopencm3
- Google protobuf
- nanopb

## Stm32f4 server
```
make -C libopencm3
bazel run //f4_proto:flash --config=arm_config
```

## Python client
```
bazel run //python_client:client
```

## C++ client
```
bazel run //client:client
```
