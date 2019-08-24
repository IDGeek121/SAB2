# Sonic Adventure Blast 2

## Required libraries
* glfw3 v3.2
* ogg
* openal-soft
* SOIL
* vorbis

## Build instructions

### Windows

For building on Windows, it is recommended to use `powershell` and `vcpkg`. `vcpkg` is a package manager that makes installing and updating libraries a snap. To set up a build environment for this project, you can run the following commands.
```
# Clone SAB2
git clone https://github.com/idgeek121/sab2.git
cd SAB2

# Clone vcpkg into the SAB2 project folder
git clone https://github.com/microsoft/vcpkg
cd vcpkg
.\bootstrap-vcpkg.bat # Build vcpkg for Windows
.\vcpkg.exe integrate project # Create a NuGet plugin for VS

# The following tells vcpkg to configure glfw3 to grab v3.2.1
git checkout -- ab0212d ports/glfw3

# Grab all the libraries (libogg is downloaded as a dependency for libvorbis)
.\vcpkg.exe install glfw3:sab2 openal-soft:sab2 soil:sab2 libvorbis:sab2
```
From there, just open NewSonicThing.sln in VS2019, make sure that the generated NuGet plugin is added to the project, then build.

### Ubuntu (and most other distros that use `APT`)

You will need to have `make` installed.
```
sudo apt update && sudo apt install libglfw3-dev libopenal-dev libsoil-dev libvorbis-dev
```
Then, clone SAB2 with git and run the packaged `makefile`
```
git clone https://github.com/idgeek121/sab2.git
cd SAB2
make
```

### Arch (and most other distros that use `pacman`)

You will need to have `make` installed.

You will need the right glfw3 package for your display server
* If on X11, install glfw3-x11 v3.2.1
```
sudo pacman -U https://archive.archlinux.org/repos/2019/04/14/community/os/x86_64/glfw-x11-3.2.1-2-x86_64.pkg.tar.xz
```
* If on Wayland, install glfw3-wayland v3.2.1
```
sudo pacman -U https://archive.archlinux.org/repos/2019/04/14/community/os/x86_64/glfw-wayland-3.2.1-2-x86_64.pkg.tar.xz
```
Install all other packages as normal.
```
sudo pacman -S libvorbis openal soil
```
Then, clone SAB2 with git and run the packaged `makefile`
```
git clone https://github.com/idgeek121/sab2.git
cd SAB2
make
```