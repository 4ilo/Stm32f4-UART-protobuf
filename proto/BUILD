proto_library(
    name = "leds_proto",
    srcs = [
        "leds.proto"
    ]
)

cc_proto_library(
    name = "leds_cc_proto",
    deps = [
        ":leds_proto"
    ],
    visibility = ["//visibility:public"],
)

# Nanopb generated protofiles
genrule(
    name = "nanopb-proto-gen",
    srcs = [
        "leds.proto",
    ],
    tools = [
        "@nanopb//:nanopb_generator",
    ],
    outs = [
        "leds.pb.c",
        "leds.pb.h",
    ],
    local = True,
    cmd = "$(location @nanopb//:nanopb_generator) $< -D $(RULEDIR)/.."
)

cc_library(
    name = "leds-proto",
    srcs = [
        "leds.pb.c",
    ],
    hdrs = [
        "leds.pb.h",
    ],
    deps = [
        "@nanopb//:nanopb",
    ],
    include_prefix = "proto",
    visibility = ["//visibility:public"],
)
