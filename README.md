# Kohibc
Follows Kohi game engine dev series provided by 


## Build Environment (For Windows and Linux only)
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

- Install Vulkan SDK:
    - Visit vulkan.lunarg.com to download the sdk.
    - Windows: Make sure %VULKAN_SDK% environment is set.
    - Linux:
        - Download the tar.xz file
        - Follow `Install SDK` section [here](https://vulkan.lunarg.com/doc/view/1.3.261.1/linux/getting_started.html)
        - Adjust the environment variables
> On my Ubuntu system: There is no way to persist derived environment variables system-wide from `VULKAN_SDK`. You might have to run `source /opt/vulkan/1.3.261.1/setup-env.sh` after each login. `VULKAN_SDK`is set using `/etc/environment` but the other env variables can NOT be set using the same method.

- [Linux Only]: 
    - For windowing: `sudo apt-get install libx11-dev libx11-xcb-dev libxkbcommon-x11-dev`
    - Give `chmod +x` permissions to *.sh files.
- Install VSCode
    - Install the following extensions:
        - Microsoft C/C++ (Required)
        - Shader Languages Support (slevesque.shader) [Optional]
    - c_cpp_properties.json:
        - windows_sdk[optional]: To find which Windows sdk is used, it might be located under `Windows Kits\10\Include\<version>`
