load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_protobuf",
    sha256 = "6dd0f6b20094910fbb7f1f7908688df01af2d4f6c5c21331b9f636048674aebf",
    strip_prefix = "protobuf-3.14.0",
    urls = [
        "https://github.com/protocolbuffers/protobuf/releases/download/v3.14.0/protobuf-all-3.14.0.tar.gz",
    ],
)
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

http_archive(
    name = "nanopb",
    sha256 = "cc3beaff146ffa0111ff92e5feac5791e6a49c5307dde4d3aae68424a53b0d3b",
    strip_prefix = "nanopb-0.4.3",
    urls = [
        "https://github.com/nanopb/nanopb/archive/0.4.3.tar.gz",
    ],
    build_file = "@//:nanopb.BUILD",
)
