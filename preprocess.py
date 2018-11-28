Import("env")

def precompile(source, target, env):
  env.Execute("node src/build.js")

env.AddPreAction("$BUILD_DIR/src/ps2msx.cpp.o", precompile)
