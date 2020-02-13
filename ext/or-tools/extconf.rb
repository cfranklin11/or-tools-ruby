require "mkmf-rice"

abort "Missing stdc++" unless have_library("stdc++")

$CXXFLAGS << " -std=c++11"

# or-tools warnings
$CXXFLAGS << " -Wno-sign-compare -Wno-shorten-64-to-32 -Wno-ignored-qualifiers"

inc, lib = dir_config("or-tools")

inc ||= "/usr/local/include"
lib ||= "/usr/local/lib"

$INCFLAGS << " -I#{inc}"

$LDFLAGS << " -Wl,-rpath,#{lib}"
$LDFLAGS << " -L#{lib}"
$LDFLAGS << " -lortools"

create_makefile("or_tools/ext")
