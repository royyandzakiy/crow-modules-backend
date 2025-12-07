```bash
# msvc
conan install . -of build-msvc --build=missing -s compiler=msvc -s compiler.version=193 -s compiler.runtime=dynamic -s compiler.cppstd=23
```