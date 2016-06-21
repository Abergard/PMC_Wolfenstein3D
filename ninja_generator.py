from ninja_syntax import Writer
import platform


class NinjaGenerator:
    def __init__(self, project_root, files, libs, main, lflags, includes, exe):
        print("BearsGenerator initializing...")
        if (self.prepareSystemVariable()):
            self.prepareCommonVariable(lflags)
            self.files = files
            self.libs = libs
            self.main = main
            self.includes = includes
            self.exe = exe
            self.project_root = project_root
            self.generate()

    def prepareSystemVariable(self):
        if (platform.system() == "Windows"):
            return self.prepareWindowsVariable()
        else:
            return self.unsupportedSystem()

    def prepareWindowsVariable(self):
        print("Detected system: Windows")
        self.rule_compile = "compile"
        self.rule_analyze = "analyze"
        self.rule_link = "link"
        self.rule_syntax_check = "syntax_check"
        self.rule_static_lib = "static_lib"
        self.rule_run = "run"
        return True

    def unsupportedSystem(self):
        print("You have unsupported system :(")
        return False

    def prepareCommonVariable(self, lflags):
        self.variables = {"compiler": "clang-cl /MDd /imsvc c:/include -c",
                          "linker": "clang-cl /MDd",
                          "analyzer": "clang++ -cxx-isystem c:/include "
                                      "--analyze",
                          "syntax_checker": "clang++ -cxx-isystem c:/include "
                                            "-fsyntax-only",
                          "lib_creator": "llvm-lib",
                          "cflags": ("-fms-compatibility-version=19 -m64 "
                                     "-Weverything "
                                     "-Wno-c++98-compat "
                                     "-Wno-c++98-compat-pedantic "
                                     "-Wno-c++98-c++11-compat-pedantic "
                                     "-Wno-undefined-func-template "
                                     "-Wno-exit-time-destructors "
                                     "-Wno-global-constructors "
                                     "-Wno-unknown-pragmas"),
                          "lflags": lflags,
                          "includes": ""}

    def generate(self):
        with open("build.ninja", "w") as buildfile:
            self.ninja_writter = Writer(buildfile)
            self.generateVariable()
            self.generateRules()
            self.generateBuilds()
            print("Completed successfully.")

    def generateVariable(self):
        print("Generating variables...")
        for key in self.variables:
            self.ninja_writter.variable(key=key, value=self.variables[key])

    def generateRules(self):
        print("Generating rules...")
        self.generateCompileRule()
        self.generateLinkRule()
        self.generateAnalyzeRule()
        self.generateSyntaxCheckRule()
        self.generateStaticLibRule()
        self.generateRunRule()

    def generateCompileRule(self):
        self.ninja_writter.newline()
        self.ninja_writter.rule(
            self.rule_compile,
            command=("$compiler $cflags $includes $in -o $out"),
            description="Building C++ filename $in")

    def generateLinkRule(self):
        self.ninja_writter.newline()
        self.ninja_writter.rule(self.rule_link,
                                command=("$linker $in -o $out /link $lflags"),
                                description="Linking to $out")

    def generateAnalyzeRule(self):
        self.ninja_writter.newline()
        self.ninja_writter.rule(
            self.rule_analyze,
            command=("$analyzer $cflags $includes $in -o $out"),
            description="Analyzing $in ...")

    def generateSyntaxCheckRule(self):
        self.ninja_writter.newline()
        self.ninja_writter.rule(
            self.rule_syntax_check,
            command=("$syntax_checker $cflags $includes $in"),
            description="Checking syntax $in ...")

    def generateStaticLibRule(self):
        self.ninja_writter.newline()
        self.ninja_writter.rule(
            self.rule_static_lib,
            command=("$lib_creator $in /out:$out"),
            description="Creating static lib from  $in ...")

    def generateRunRule(self):
        self.ninja_writter.newline()
        self.ninja_writter.rule(self.rule_run, command=(self.exe))

    def generateBuilds(self):
        print("Generating builds...")
        self.generateMainModule()
        self.generateLibModules()
        self.generateBinaryBuild()
        self.generateAnalyzeBuild()
        self.generateSyntaxBuild()
        self.generateRunBuild()
        self.generateDefault()

    def generateMainModule(self):
        self.generateModuleBuild(self.main)

    def generateModuleBuild(self, modulename):
        self.ninja_writter.newline()
        self.ninja_writter.comment(" ---------------------" + "Module: " +
                                   modulename + " ---------------------")
        self.generateBuild("Compile", modulename, self.rule_compile, ".cpp",
                           ".o")
        self.generateBuild("Analyze", modulename, self.rule_analyze, ".cpp",
                           ".plist")
        self.generateSyntaxCheckBuildFlag(modulename)

    def generateLibModules(self):
        for modulename in self.libs:
            self.generateModuleBuild(modulename)
            self.generateStaticLibBuild(modulename)

    def generateBinaryBuild(self):
        self.ninja_writter.newline()
        self.ninja_writter.comment(" ---------------------" + "Binary: " +
                                   self.exe + " ---------------------")
        self.ninja_writter.build(outputs=self.exe,
                                 rule=self.rule_link,
                                 inputs=self.getLinkerArgument())

    def generateDefault(self):
        self.ninja_writter.newline()
        self.ninja_writter.comment(
            " ------------------------------------------")
        self.ninja_writter.default(self.exe)

    def generateAnalyzeBuild(self):
        self.ninja_writter.newline()
        self.ninja_writter.comment(
            " ------------------------------------------")
        files = []
        for module in self.files:
            for file in self.files[module]:
                files.append("./build/" + file + ".plist")
        self.ninja_writter.build(outputs="analyze",
                                 rule="phony",
                                 implicit=files)

    def generateSyntaxBuild(self):
        self.ninja_writter.newline()
        self.ninja_writter.comment(
            " ------------------------------------------")
        modules = []
        for module in self.files:
            modules.append("syntax_check_" + module)
        self.ninja_writter.build(outputs="syntax",
                                 rule="phony",
                                 implicit=modules)

    def generateRunBuild(self):
        self.ninja_writter.newline()
        self.ninja_writter.comment(
            " ------------------------------------------")
        self.ninja_writter.build(outputs=self.rule_run,
                                 rule=self.rule_run,
                                 inputs=self.exe)

    def generateBuild(self, build_name, modulename, rule, in_ext, out_ext):
        self.ninja_writter.newline()
        self.ninja_writter.comment(build_name)
        for filename in self.files[modulename]:
            if self.includes[modulename]:
                self.ninjaWriteWithExtraIncludes(filename, modulename, rule,
                                                 in_ext, out_ext,
                                                 self.includes[modulename])
            else:
                self.ninjaWriteWithoutExtraIncludes(filename, modulename, rule,
                                                    in_ext, out_ext)

    def generateStaticLibBuild(self, modulename):
        self.ninja_writter.newline()
        self.ninja_writter.comment("Creation lib")
        self.ninja_writter.build(outputs="./build/" + modulename + ".lib",
                                 rule=self.rule_static_lib,
                                 inputs=self.getListOfFileInModule(
                                     modulename, "./build", ".o"))

    def generateSyntaxCheckBuildFlag(self, modulename):
        self.ninja_writter.newline()
        self.ninja_writter.comment("Syntax check")
        if (self.includes[modulename]):
            self.ninja_writter.build(
                outputs="syntax_check_" + modulename,
                rule=self.rule_syntax_check,
                inputs=self.getListOfFileInModule(
                    modulename, self.project_root + "/" + modulename, ".cpp"),
                variables={"includes":
                           "$includes " + self.includes[modulename]})
        else:
            self.ninja_writter.build(outputs="syntax_check_" + modulename,
                                     rule=self.rule_syntax_check,
                                     inputs=self.getListOfFileInModule(
                                         modulename,
                                         self.project_root + "/" + modulename,
                                         ".cpp"))

    def getListOfFileInModule(self, modulename, directory, ext):
        file_to_lib = []
        for filename in self.files[modulename]:
            file_to_lib.append(directory + "/" + filename + ext)
        return file_to_lib

    def ninjaWriteWithoutExtraIncludes(self, filename, modulename, rule,
                                       in_ext, out_ext):
        self.ninja_writter.build(
            outputs="./build/" + filename + out_ext,
            rule=rule,
            inputs=self.project_root + "/" + modulename + "/" + filename +
            in_ext)

    def ninjaWriteWithExtraIncludes(self, filename, modulename, rule, in_ext,
                                    out_ext, extra_include):
        self.ninja_writter.build(
            outputs="./build/" + filename + out_ext,
            rule=rule,
            inputs=self.project_root + "/" + modulename + "/" + filename +
            in_ext,
            variables={"includes": "$includes " + extra_include})

    def getLinkerArgument(self):
        main = []
        for filename in self.files[self.main]:
            main.append("./build/" + filename + ".o")
        for lib in self.libs:
            main.append("./build/" + lib + ".lib")
        return main
