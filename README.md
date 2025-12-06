```bash
# clang
conan install . -of build-clang --build=missing -s compiler=clang -s compiler.version=20 -s compiler.runtime_type=Release -s compiler.cppstd=23

# msvc
conan install . -of build-msvc --build=missing -s compiler=msvc -s compiler.version=193 -s compiler.runtime=dynamic -s compiler.cppstd=23
```