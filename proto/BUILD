load("@com_google_protobuf//:protobuf.bzl", "py_proto_library")

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

py_proto_library(
    name = "leds_py_proto",
    srcs = [
        "leds.proto"
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
    cmd = "$(location @nanopb//:nanopb_generator) $< -D $$(dirname $(RULEDIR))"
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
