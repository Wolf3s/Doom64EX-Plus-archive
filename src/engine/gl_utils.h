// Emacs style mode select   -*- C -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 2007-2012 Samuel Villarreal
// Copyright(C) 2022 André Guilherme
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//
// DESCRIPTION:
//		It stores some OpenGL utils here:
// 
//-----------------------------------------------------------------------------
#include <math.h>

#include "gl_main.h"

#include "doomtype.h" //Include all types neccessary.

#ifdef USE_GLFW
#include <GLFW/glfw3.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif

//André: Use this as wrapper to all the functions.
#ifdef USE_GLFW

#define OGL_RED GLFW_RED_BITS
#define OGL_GREEN GLFW_GREEN_BITS
#define OGL_BLUE GLFW_BLUE_BITS
#define OGL_ALPHA GLFW_ALPHA_BITS
#define OGL_BUFFER GLFW_AUX_BUFFERS
#define OGL_DOUBLEBUFFER GLFW_DOUBLEBUFFER
#define OGL_DEPTH GLFW_DEPTH_BITS
#define OGL_STENCIL GLFW_STENCIL_BITS
#define OGL_ACCUM_RED GLFW_ACCUM_RED_BITS 
#define OGL_ACCUM_GREEN GLFW_ACCUM_GREEN_BITS 
#define OGL_ACCUM_BLUE GLFW_ACCUM_BLUE_BITS
#define OGL_ACCUM_ALPHA GLFW_ACCUM_ALPHA_BITS 
#define OGL_STEREO GLFW_STEREO 
#define OGL_MULTISAMPLE_BUFFERS 0//Dummy
#define OGL_MULTISAMPLE 0//Dummy
#define OGL_ACCELERATED 0//Dummy
#define OGL_RETAINED 0//Dummy
#define OGL_MAJOR_VERSION GLFW_VERSION_MAJOR
#define OGL_MINOR_VERSION GLFW_VERSION_MINOR
#define OGL_CONTEXT GLFW_CONTEXT_CREATION_API
#define OGL_CONTEXT_FLAGS 0//Dummy
#define OGL_CONTEXT_PROFILE 0//Dummy
#define OGL_CURRENT_CONTEXT 0//Dummy
#define OGL_FRAMEBUFFER 0//Dummy
#define OGL_CONTEXT_RELEASE GLFW_CONTEXT_RELEASE_BEHAVIOR
#define OGL_CONTEXT_RESET GLFW_LOSE_CONTEXT_ON_RESET
#define OGL_CONTEXT_NO_ERROR GLFW_CONTEXT_NO_ERROR
#define OGL_CONTEXT_FLOATBUFFERS 0//Wip.

#define OGL_WINDOW_HINT(hint, value) glfwWindowHint(hint, value)
#define OGL_DESTROY_WINDOW(window) glfwTerminate();
#define OGL_DEFS	\
GLFWwindow *Window	\

#else
#define OGL_RED SDL_GL_RED_SIZE
#define OGL_GREEN SDL_GL_GREEN_SIZE
#define OGL_BLUE SDL_GL_BLUE_SIZE
#define OGL_ALPHA SDL_GL_ALPHA_SIZE
#define OGL_BUFFER SDL_GL_BUFFER_SIZE
#define OGL_DOUBLEBUFFER SDL_GL_DOUBLEBUFFER
#define OGL_DEPTH SDL_GL_DEPTH_SIZE
#define OGL_STENCIL SDL_GL_STENCIL_SIZE
#define OGL_ACCUM_RED SDL_GL_ACCUM_RED_SIZE
#define OGL_ACCUM_GREEN SDL_GL_ACCUM_GREEN_SIZE
#define OGL_ACCUM_BLUE SDL_GL_ACCUM_BLUE_SIZE
#define OGL_ACCUM_ALPHA SDL_GL_ACCUM_ALPHA_SIZE
#define OGL_STEREO SDL_GL_STEREO
#define OGL_MULTISAMPLE_BUFFERS SDL_GL_MULTISAMPLEBUFFERS
#define OGL_MULTISAMPLE SDL_GL_MULTISAMPLESAMPLES
#define OGL_ACCELERATED SDL_GL_ACCELERATED_VISUAL
#define OGL_RETAINED SDL_GL_RETAINED_BACKING
#define OGL_MAJOR_VERSION SDL_GL_CONTEXT_MAJOR_VERSION
#define OGL_MINOR_VERSION SDL_GL_CONTEXT_MINOR_VERSION
#define OGL_CONTEXT SDL_GL_CONTEXT_EGL
#define OGL_CONTEXT_FLAGS SDL_GL_CONTEXT_FLAGS
#define OGL_CONTEXT_PROFILE SDL_GL_CONTEXT_PROFILE_MASK
#define OGL_CURRENT_CONTEXT SDL_GL_SHARE_WITH_CURRENT_CONTEXT
#define OGL_FRAMEBUFFER SDL_GL_FRAMEBUFFER_SRGB_CAPABLE
#define OGL_CONTEXT_RELEASE SDL_GL_CONTEXT_RELEASE_BEHAVIOR
#define OGL_CONTEXT_RESET SDL_GL_CONTEXT_RESET_NOTIFICATION
#define OGL_CONTEXT_NO_ERROR SDL_GL_CONTEXT_NO_ERROR
#define OGL_CONTEXT_FLOATBUFFERS SDL_GL_FLOATBUFFERS
#define OGL_DOUBLE_BUFFER SDL_GL_DOUBLEBUFFER
#define OGL_WINDOW_HINT(attr, value) SDL_GL_SetAttribute(attr, value)
#define OGL_DESTROY_WINDOW(context) SDL_GL_DeleteContext(context)
#define OGL_DEFS    \
SDL_GLContext   Window
#endif
//
// CUSTOM ROUTINES
//
void glSetVertex(vtx_t* vtx);
void glTriangle(int v0, int v1, int v2);
void glDrawGeometry(dword count, vtx_t* vtx);
void glViewFrustum(int width, int height, rfloat fovy, rfloat znear);
void glSetVertexColor(vtx_t* v, rcolor c, word count);
void glGetColorf(rcolor color, float* argb);
void glTexCombReplace(void);
void glTexCombColor(int t, rcolor c, int func);
void glTexCombColorf(int t, float* f, int func);
void glTexCombModulate(int t, int s);
void glTexCombAdd(int t, int s);
void glTexCombInterpolate(int t, float a);
void glTexCombReplaceAlpha(int t);
void glGetVersion(int major, int minor);
void glDestroyWindow(OGL_DEFS);


//
// GL_ARB_multitexture
//
extern PFNGLACTIVETEXTUREARBPROC _glActiveTextureARB;

#define glActiveTextureARB(texture) _glActiveTextureARB(texture)