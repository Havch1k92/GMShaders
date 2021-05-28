# Garry's Mod Shader Hotloader

### Allows you to inject pixel/vertex shaders in-game using Lua
cba to maintain this since I don't play the game anymore
I doubt that signature could change but it's probably outdated by now

---
Folder `Shaders/` contains a sample cpp file implementing a lensflare from *Estranged ACT I* (was using it for testing purposes).
`Shaders/fxc/` contains a compiled sample lensflare shader and a static library `shaderlib.lib`. You need to link it in your project settings.

You will also need a copy of **SourceSDK** and a **detouring** library.
There is also a `platform.hpp` file from my unfinished library containing useful macros for code portability.

You can find a sample LUA script in the `lua/` folder, run it to apply the sample lensflare material
