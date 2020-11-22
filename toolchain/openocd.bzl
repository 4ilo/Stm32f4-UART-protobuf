
def _openocd_flash_impl(ctx):
    out = ctx.actions.declare_file(ctx.label.name)

    binary = ctx.attr.binary.files.to_list()[0]
    cmd = [
        "openocd",
        "-f {}".format(ctx.attr.config_file),
        "-c 'program {} verify reset exit'".format(binary.short_path)
    ]

    ctx.actions.write(out, " ".join(cmd), is_executable=True)

    return [
        DefaultInfo(
            executable=out,
            runfiles = ctx.runfiles([binary])
        )
    ]

openocd_flash = rule(
    _openocd_flash_impl,
    executable = True,
    attrs = {
        "binary": attr.label(),
        "config_file": attr.string(),
    }
)
