# Kohibc
Follows Kohi game engine dev series provided by 


## Build Environment (For Windows and Linux only)
- Install Clang
    - Windows: Use Visual Studio Installer and type Clang to install the required packages
        - Navigate to C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build and run `vcvarsall.bat x64`
        - Also find the location of `clang.exe` (to be used in vscode settings) and append it to the path
    - Linux:
    - Make sure `clang` is installed by running `clang-cl --version` or `clang --version`
- Install Vulkan SDK:
    - Visit vulkan.lunarg.com to download the sdk.
    - Windows: Make sure %VULKAN_SDK% environment is set.

- Install VSCode
    - Install the following extensions:
        - Microsoft C/C++ (Required)
        - Shader Languages Support (slevesque.shader) [Optional]
    - c_cpp_properties.json:
        - windows_sdk[optional]: To find which Windows sdk is used, it might be located under `Windows Kits\10\Include\<version>`
