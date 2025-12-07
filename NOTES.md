```bash
# msvc
rmdir /s /q build-msvc
 && conan install . -of build-msvc --build=missing -s compiler=msvc -s compiler.version=193 -s compiler.runtime=dynamic -s compiler.cppstd=23
```

- Choose Configure Preset: "conan-default"
- Build, Run