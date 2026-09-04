// Milestone 3 smoke test: open an SDL window, create a real OpenGL context
// against it, clear to a distinct color every frame and present it.
//
// Deliberately standalone (its own window, its own exe) rather than wired
// into gxRuntime/Graphics3D - the D3D7 pipeline still owns that window and
// isn't touched by this. This just proves the GL toolchain (SDL_GL_*, a
// 32-bit context, opengl32.lib linkage) works in this build environment
// before milestone 4 tries to actually draw something through a real
// render loop.
//
// No GL loader (GLAD etc.) yet - glClearColor/glClear/glGetString are core
// 1.0 and come straight from opengl32.lib's static import lib. A loader
// only becomes necessary once shaders/VBOs (milestone 4+) are needed.

// gl/GL.h relies on WINGDIAPI/APIENTRY, which it expects windows.h to have
// already defined - include order matters here.
#include <windows.h>
// Without this, SDL.h #defines main to SDL_main (via SDL_main.h) expecting
// SDL2main.lib to provide the real entry point - we're not linking that,
// so keep our own plain main().
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <gl/GL.h>
#include <cstdio>

int main( int argc,char *argv[] ){

	if( SDL_Init( SDL_INIT_VIDEO )!=0 ){
		std::fprintf( stderr,"SDL_Init failed: %s\n",SDL_GetError() );
		return 1;
	}

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,24 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1 );

	SDL_Window *window=SDL_CreateWindow(
			"blitz3dgl - milestone 3: GL context",
			SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
			800,600,
			SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN );

	if( !window ){
		std::fprintf( stderr,"SDL_CreateWindow failed: %s\n",SDL_GetError() );
		SDL_Quit();
		return 1;
	}

	SDL_GLContext gl_ctx=SDL_GL_CreateContext( window );
	if( !gl_ctx ){
		std::fprintf( stderr,"SDL_GL_CreateContext failed: %s\n",SDL_GetError() );
		SDL_DestroyWindow( window );
		SDL_Quit();
		return 1;
	}

	SDL_GL_SetSwapInterval( 1 );

	std::printf( "GL_VERSION:  %s\n",glGetString( GL_VERSION ) );
	std::printf( "GL_VENDOR:   %s\n",glGetString( GL_VENDOR ) );
	std::printf( "GL_RENDERER: %s\n",glGetString( GL_RENDERER ) );
	std::printf( "Milestone 3: window+context up. Rendering a clear color - Esc or close to quit.\n" );

	bool running=true;
	while( running ){
		SDL_Event ev;
		while( SDL_PollEvent( &ev ) ){
			if( ev.type==SDL_QUIT ) running=false;
			if( ev.type==SDL_KEYDOWN && ev.key.keysym.sym==SDLK_ESCAPE ) running=false;
		}

		// Distinct, unmistakably-not-black clear color - proves the GL
		// pipeline (not just a black D3D-style window) is actually live.
		glClearColor( 0.15f,0.45f,0.80f,1.0f );
		glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );

		SDL_GL_SwapWindow( window );
	}

	SDL_GL_DeleteContext( gl_ctx );
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
