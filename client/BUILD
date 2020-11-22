cc_binary(
    name = "client",
    srcs = [
        "main.cpp",
        "serial.cpp",
        "serial.h",
    ],
    deps = [
        "//proto:leds_cc_proto",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Werror",
    ],
    linkopts = [
        "-std=c++11",
    ]
)
