package(default_visibility = ["//visibility:public"])

cc_library(
  name = "nanopb",
  visibility = ["//visibility:public"],
  hdrs = [
    "pb.h",
    "pb_common.h",
    "pb_decode.h",
    "pb_encode.h",
  ],
  srcs = [
    "pb_common.c",
    "pb_decode.c",
    "pb_encode.c",
  ],
  strip_include_prefix = "",
)

py_binary(
    name = "nanopb_generator",
    main = "generator/nanopb_generator.py",
    srcs = glob(["generator/**/*.py"]),
    imports = [
        "generator",
    ],
)
