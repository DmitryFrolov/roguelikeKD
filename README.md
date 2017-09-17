# Setup project
### Windows
 - Open RoguelikeGame.sln
 - set active configuration to Debug & x86
 - run

### Linux
 - make sure you have installed next packages
   ```sh
	libsdl2-2.0-0 
	libsdl2-image-2.0-0 
	libsdl2-mixer-2.0-0
	libsdl2-net-2.0-0
	libsdl2-ttf-2.0-0
	```
 - build project
   ```sh
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make
   ```
