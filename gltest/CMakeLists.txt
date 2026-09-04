cmake_minimum_required(VERSION 3.16)

project(gltest)

# Standalone milestone-3 smoke test (own window/exe, not linked into the
# real Blitz3D runtime) - see gltest/main.cpp for why.
add_executable(gltest
		main.cpp
		)

set(SDL2_ROOT ${CMAKE_SOURCE_DIR}/third_party/SDL2)
target_include_directories(gltest PRIVATE ${SDL2_ROOT}/include)
# Plain console main() (not WinMain via SDL_main), so SDL2main.lib is
# deliberately not linked here - it would collide with our own main().
target_link_libraries(gltest ${SDL2_ROOT}/lib/x86/SDL2.lib opengl32)

add_custom_command(TARGET gltest POST_BUILD VERBATIM
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:gltest> ${CMAKE_SOURCE_DIR}/BLITZ3D_INSTALL/bin/gltest.exe
		COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_ROOT}/lib/x86/SDL2.dll ${CMAKE_SOURCE_DIR}/BLITZ3D_INSTALL/bin/SDL2.dll)
