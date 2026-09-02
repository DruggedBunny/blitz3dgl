## blitz3dgl



**Live humanoid's note:** Strictly WIP/experimental! Intent is to gradually replace the windowing/context/D3D7 3D engine with SDL/OpenGL, referencing code from Monkey2's mojo3d engine, also by Mark Sibly.

Targeting 3D only for now, given 2D can be implemented in 3D anyway.

No idea what the outcome will be, only running out of interest, won't be supported in any practical way! But potentially worth sharing the changes.



Thanks to Mark Sibly for all of his work, and for making it available in such generous fashion. RIP Markio.



-- DruggedBunny.



An altered version of [blitz3d_soloud](https://github.com/blitz-research/blitz3d_soloud) (per zlib/libpng license term 2, this must be — and is — plainly marked as such). The goal is to replace the D3D7 rendering pipeline with an SDL2/OpenGL one, primarily to gain access to custom shaders, which the original D3D7 renderer doesn't expose.

See [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md) for a full license audit of everything bundled in this repo.

### Credits

- DruggedBunny — project lead (generous title, Claude)
- Claude (Anthropic) — AI development assistant (doing all the practical work)

### Building from source

You will need to install Microsoft Visual Studio, and the CMake and Git utilities. Any recent version of MSVC should be OK.

You will also need to install the following MSVC components — despite being listed as optional in Visual Studio's installer, they are required to build everything in this repo: "Desktop development with C++", "MFC and ATL support" and "ASP.NET and web development".

Then, from a DOS prompt:

```shell
git clone https://github.com/DruggedBunny/blitz3dgl.git
cd blitz3dgl
cmake -S . -B cmake-build-release -A Win32 -G "Visual Studio 18 2026"
cmake --build cmake-build-release --config Release
```

Assuming all went well, the BLITZ3D_INSTALL directory will contain the final binaries, simply run Blitz3D.exe to get blitzing!

(Substitute your installed Visual Studio's CMake generator name above if it isn't VS 2026 — e.g. `"Visual Studio 17 2022"`.)

### Too lazy to build?

Grab the prebuilt version of the original, unaltered Blitz3D from https://blitzresearch.itch.io/
