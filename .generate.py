from external.ninja_generator.ninja_generator import NinjaGenerator

project_root = "./src"
main = "core"
libs = {}
exe = "Wolfenstein3D.exe"

files = {"core": {"Camera", "Graphics", "Main", "Objectclass"}}

includes = {"core": None}

lflags = ("Gdi32.lib "
          "User32.lib "
          "glu32.lib "
          "opengl32.lib")

if __name__ == "__main__":
    NinjaGenerator(project_root, files, libs, main, lflags, includes, exe)
