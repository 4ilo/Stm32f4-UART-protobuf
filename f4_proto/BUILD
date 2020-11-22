load("//toolchain:openocd.bzl", "openocd_flash")

cc_binary(
    name = "f4_proto",
    srcs = [
        "main.c"
    ],
    deps = [
        "//libopencm3:export",
        "//libopencm3:libopencm3_stm32f4",
        "//proto:leds-proto",
        "@nanopb//:nanopb",
        "stm32f411vet6.ld",
    ],
    defines = [
        "STM32F4",
        "STM32F411VET6"
    ],
    copts = [
        "-Wall",
        "-Werror",
        "-Wextra",
        "-Wimplicit-function-declaration",
        "-Wmissing-prototypes",
        "-Wno-unused-variable",
        "-Wredundant-decls",
        "-Wshadow",
        "-Wstrict-prototypes",
        "-fdata-sections",
        "-ffunction-sections",
        "-fno-common",
    ],
    linkopts = [
        "-T$(location stm32f411vet6.ld)",
        "-specs=nano.specs",
    ]
)

openocd_flash(
    name = "flash",
    binary = ":f4_proto",
    config_file = "board/stm32f4discovery.cfg",
)
