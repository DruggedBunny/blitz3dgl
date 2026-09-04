// Milestones 3+4 smoke test: open an SDL window, create a real OpenGL
// context against it, and render something every frame.
// - Milestone 3: clear to a distinct color.
// - Milestone 4: also draw one hardcoded triangle, proving the render loop
//   itself (clear -> draw -> swap, every frame) works - still bypasses
//   gxMesh entirely, just fixed-function immediate-mode geometry.
//
// Deliberately standalone (its own window, its own exe) rather than wired
// into gxRuntime/Graphics3D - the D3D7 pipeline still owns that window and
// isn't touched by this.
//
// No GL loader (GLAD etc.) yet - glClearColor/glClear/glGetString/
// glBegin+friends are all core 1.0 and come straight from opengl32.lib's
// static import lib. A loader only becomes necessary once shaders/VBOs
// are needed (milestone 5, porting the real gxMesh->GL path).

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

	// Match gxRuntime's own fix for the exact same bug (see project memory:
	// "DPI-unaware window scaling bug") - must be called before the first
	// window is created, or Windows silently upscales this standalone
	// window's pixel dimensions on a scaled display.
	SetProcessDPIAware();

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
			"blitz3dgl - milestone 4: hardcoded triangle",
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

	int drawable_w,drawable_h;
	SDL_GL_GetDrawableSize( window,&drawable_w,&drawable_h );
	glViewport( 0,0,drawable_w,drawable_h );

	std::printf( "GL_VERSION:  %s\n",glGetString( GL_VERSION ) );
	std::printf( "GL_VENDOR:   %s\n",glGetString( GL_VENDOR ) );
	std::printf( "GL_RENDERER: %s\n",glGetString( GL_RENDERER ) );
	std::printf( "Drawable size: %dx%d\n",drawable_w,drawable_h );
	std::printf( "Milestone 4: rendering one hardcoded triangle every frame - Esc or close to quit.\n" );

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

		// One hardcoded triangle, straight in clip space (no matrix setup
		// needed - the fixed-function modelview/projection matrices default
		// to identity) - proves clear->draw->swap works as a real per-frame
		// loop, still entirely bypassing gxMesh/gxScene.
		glBegin( GL_TRIANGLES );
			glColor3f( 1.0f,0.2f,0.2f ); glVertex2f(  0.0f,  0.6f );
			glColor3f( 0.2f,1.0f,0.2f ); glVertex2f( -0.6f, -0.5f );
			glColor3f( 0.2f,0.4f,1.0f ); glVertex2f(  0.6f, -0.5f );
		glEnd();

		SDL_GL_SwapWindow( window );
	}

	SDL_GL_DeleteContext( gl_ctx );
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
