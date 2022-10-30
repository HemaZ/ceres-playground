from conans import ConanFile, CMake


class CeresPlayground(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "ceres-solver/2.1.0", "eigen/3.4.0"
    generators = "cmake"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")  # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib")  # From lib to bin

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
