# Third-party licenses

This project's own code is licensed under the zlib/libpng license — see [LICENSE.TXT](LICENSE.TXT).

Project policy: new external dependencies must be MIT, zlib/libpng, BSD, public domain, or an
equivalently permissive license. The one exception below (FreeImage) predates this policy and was
kept deliberately — see its entry for the reasoning.

## Bundled / linked components

| Component | Location | License | Permissive? |
|---|---|---|---|
| Blitz3D core (compiler, linker, runtime, gxruntime, IDE, debugger) | repo root | zlib/libpng | Yes |
| [SoLoud](https://github.com/blitz-research/soloud) | fetched at build time via CMake `FetchContent` (`soloud/CMakeLists.txt`), not vendored | zlib/libpng | Yes |
| [stb_vorbis](https://github.com/nothings/stb) (Sean Barrett) | bundled inside SoLoud's `src/audiosource/wav/stb_vorbis.c` | Public domain / MIT (dual) | Yes |
| LibJPEG (IJG) | `freeimage/LibJPEG` | Independent JPEG Group License | Yes |
| LibPNG | `freeimage/LibPNG` (license text: `freeimage/LibPNG/LICENSE`) | libpng license | Yes |
| ZLib | `freeimage/ZLib` | zlib license | Yes |
| **FreeImage** | `freeimage/FreeImage`, `freeimage/*.h` | **FreeImage Public License (FIPL, MPL-1.1–derived)** | **Not strictly** — see note below |
| LibMNG, LibTIFF | `freeimage/LibMNG`, `freeimage/LibTIFF` | zlib-style / libtiff license (permissive) | Yes, but **unused** — not referenced by `freeimage/CMakeLists.txt`, dead weight in the tree |

## Note on FreeImage

FreeImage (the wrapper library around LibJPEG/LibPNG/ZLib used for texture and image loading) is
licensed under the FreeImage Public License, an MPL-1.1–derived license. Unlike the other
components above, it isn't strictly MIT/zlib-class: it requires that *modifications to FreeImage's
own source files* be made available under FIPL. It does **not** require the rest of this project
to be open-sourced, and commercial use is explicitly permitted.

Decision (2026-09-02): keep FreeImage as-is rather than replace it with a stricter-permissive
alternative (e.g. `stb_image`, public domain/MIT) — replacing it means rewriting every texture/image
loading call site, which is real engineering work, not a documentation change. Revisit if this
becomes a real blocker.

## Going forward

Anything added later for the SDL2/OpenGL renderer work (SDL2 itself is zlib-licensed; a GL loader
such as GLAD is public domain/MIT-generated code) should be checked against the policy above before
it's added, and this table updated to match.
