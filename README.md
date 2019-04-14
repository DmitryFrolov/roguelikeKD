# About

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5b5e294f070e4a97a5e4e1b5e059d5c1)](https://app.codacy.com/app/DmitryFrolov/roguelikeKD?utm_source=github.com&utm_medium=referral&utm_content=DmitryFrolov/roguelikeKD&utm_campaign=Badge_Grade_Dashboard)

Simple 2d roguelike game developed as demo for SDLEngine library.

# Setup project
### Windows
 - Open RoguelikeGame.sln
 - set active configuration to Debug & x86
 - run

### Linux
 Build project
   ```sh
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make
   ```
Executable file and game resources will be placed in bin/ directory

### Windows
 Build project
   ```sh
   $ mkdir build
   $ cd build
   $ cmake -G "Visual Studio 15 2017" ../
   ```
Visual Studio Project files will be generated after running this command. Open. Build. Run.
