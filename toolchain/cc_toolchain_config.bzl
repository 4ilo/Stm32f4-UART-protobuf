load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")
load(
   "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
   "feature",
   "flag_group",
   "flag_set",
   "tool_path",
)

all_link_actions = [
   ACTION_NAMES.cpp_link_executable,
   ACTION_NAMES.cpp_link_dynamic_library,
   ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]
all_compile_actions = [
   ACTION_NAMES.c_compile,
   ACTION_NAMES.cpp_compile,
   ACTION_NAMES.cpp_module_compile,
]

def _impl(ctx):
    path_prefix = "/usr/bin/arm-none-eabi-"

    tool_paths = [
        tool_path(
            name = "gcc",
            path = path_prefix + "gcc",
        ),
        tool_path(
            name = "ld",
            path = path_prefix + "ld",
        ),
        tool_path(
            name = "ar",
            path = path_prefix + "ar",
        ),
        tool_path(
            name = "objcopy",
            path = path_prefix + "objcopy",
        ),
        tool_path(
            name = "cpp",
            path = "/bin/false",
        ),
        tool_path(
            name = "gcov",
            path = "/bin/false",
        ),
        tool_path(
            name = "nm",
            path = "/bin/false",
        ),
        tool_path(
            name = "objdump",
            path = "/bin/false",
        ),
        tool_path(
            name = "strip",
            path = "/bin/false",
        ),
    ]

    features = [
       feature(
           name = "default_linker_flags",
           enabled = True,
           flag_sets = [
               flag_set(
                   actions = all_link_actions,
                   flag_groups = ([
                       flag_group(
                           flags = [
                            "-Wl,--gc-sections",
                            "-mcpu=cortex-m4",
                            "-mfloat-abi=hard",
                            "-mfpu=fpv4-sp-d16",
                            "-mthumb",
                            "-nostartfiles",
                           ],
                       ),
                   ]),
               ),
               flag_set(
                   actions = all_compile_actions,
                   flag_groups = ([
                       flag_group(
                           flags = [
                            "-mcpu=cortex-m4",
                            "-mfloat-abi=hard",
                            "-mfpu=fpv4-sp-d16",
                            "-mthumb",
                           ],
                       ),
                   ]),
               ),
           ],
       ),
    ]
    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = [
            "/usr/arm-none-eabi/include",
            "/usr/lib/gcc/arm-none-eabi/10.2.0/include",
            "/usr/lib/gcc/arm-none-eabi/10.2.0/include-fixed",
        ],
        toolchain_identifier = "k8-toolchain",
        host_system_name = "local",
        target_system_name = "stm32f4",
        target_cpu = "k8",
        target_libc = "unknown",
        compiler = "arm-none-eabi",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)
