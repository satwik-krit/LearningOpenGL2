# LearningOpenGL2
## Install Instructions
Files/Libraries not included with the repo are:
1. The static lib file of `GLFW`
    - Download the appropriate version from [here](https://www.glfw.org/download.html).
    - Used for window management, context creation and event polling.

2. [`GLM`](https://github.com/g-truc/glm) - 1.0.1
	- Used for 3D math.
	- Download the release from [here](https://github.com/g-truc/glm/releases/tag/1.0.1) and copy the `glm` folder into `Dependencies/GLM/include`.

3. [`ASSIMP`](https://github.com/assimp/assimp/) - 6.0.2
	- Used for model loading
	- Go through the build instructions given in [Build.md](https://github.com/assimp/assimp/blob/master/Build.md). For this project,
		1. Download the source code from [here](https://github.com/assimp/assimp/releases/tag/v6.0.2) and extract the files (to any dir)
		2. Run the `cmake` program and ensure `ASSIMP_BUILD_ASSIMP_TOOLS` is enabled. Select the appropriate compiler version (`VS 2019`)
		3. Open `Visual Studio` and build the solution.
		4. Navigate to `build` in the extracted folder and copy the `.dll` to `Dependencies/assimp/lib`. Copy the `.lib` file from `build/lib` to the same folder. Visual Studio will automatically place the `dll` with the executable.
		5. Copy the `include` directory from `build` to `Dependencies/assimp`
