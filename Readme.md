# Stm32F4 protobuf over UART example

- Stm32f4 microcontoller
- Libopencm3
- Google protobuf
- nanopb
- Bazel

## Stm32f4 server
```
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
