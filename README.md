# Kohibc
Follows Kohi game engine dev series provided by 

## Original Repo
- [Commits](https://github.com/travisvroman/kohi/commits/main?after=21ee30466ad65a45b39514723af65912d409fc1e+279&branch=main&qualified_name=refs%2Fheads%2Fmain)
## Build Environment (For Windows and Linux only)
- Install CMake:
    - [FileSet headers usage sample](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)
    - [Discussion](https://gitlab.kitware.com/cmake/cmake/-/issues/22468)
- Install Clang
    - Windows: Use Visual Studio Installer and type Clang to install the required packages
        - Navigate to C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build and run `vcvarsall.bat x64`
        - Also find the location of `clang.exe` (to be used in vscode settings) and append it to the path
        - Make sure `clang` is installed by running `clang-cl --version` or `clang --version`
    - Linux: There are two ways to install clang:
        1. Run `sudo apt install clang lldb lld`. (Check the installation by running `clang --version`)
        2. Visit `https://apt.llvm.org/` and run the following script.
```bash
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh <version number>
# Check installation by running `clang-16 --version` or `clang++-16 --version` 
```

- Install Vulkan SDK: Vulkan can be installed using different ways
    1. Manual installation:
         - Visit vulkan.lunarg.com to download the sdk.
         - Windows: Make sure %VULKAN_SDK% environment is set.
    - Linux:
        - Download the tar.xz file
        - Follow `Install SDK` section [here](https://vulkan.lunarg.com/doc/view/1.3.261.1/linux/getting_started.html)
        - Adjust the environment variables
> On my Ubuntu system: There is no way to persist derived environment variables system-wide from `VULKAN_SDK`. You might have to run `source /opt/vulkan/1.3.261.1/setup-env.sh` after each login. `VULKAN_SDK`is set using `/etc/environment` but the other env variables can NOT be set using the same method.
    - CMake - `FetchContent` module
        - https://stackoverflow.com/questions/69144529/vulkan-hpp-with-cmake
        - https://github.com/KhronosGroup/Vulkan-Headers/issues/157
        - https://github.com/KhronosGroup/Vulkan-Headers/pull/318

- [Linux Only]: 
    - For windowing: `sudo apt-get install libx11-dev libx11-xcb-dev libxkbcommon-x11-dev`
    - Give `chmod +x` permissions to *.sh files.
- Install VSCode
    - Install the following extensions:
        - Microsoft C/C++ (Required)
        - Shader Languages Support (slevesque.shader) [Optional]
    - c_cpp_properties.json:
        - windows_sdk[optional]: To find which Windows sdk is used, it might be located under `Windows Kits\10\Include\<version>`

## Notes
- `include <assert.h>` is required for `_Static_assert keyword` or `static_assert macro` for stdc11 or higher. No longer needed since C/C++ 23. [ref1](https://en.cppreference.com/w/c/language/_Static_assert) - [ref2](https://learn.microsoft.com/en-us/cpp/c-language/static-assert-c?view=msvc-170)

### Memory subsystem
We want to control how and when the allocations occur.
- Limit dynamic memory allocations
