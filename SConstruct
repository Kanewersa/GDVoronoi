#!/usr/bin/env python
import os
import sys
import pdb

CacheDir('.scons-cache/')

env = SConscript("godot-cpp/SConstruct")

# Add source files
env.Append(CPPPATH=["src/", "lib/voronoi/src/"])
sources = Glob("src/*.cpp") + Glob("src/godot/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/bin/libvoronoi.{}.{}.framework/libvoronoi.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "demo/bin/libvoronoi{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
