/* This file is part of SDL_gles - SDL addon for OpenGL|ES
 * Copyright (C) 2010 Javier S. Pedro
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA or see <http://www.gnu.org/licenses/>.
 */

#ifndef __SDL_GLES_H
#define __SDL_GLES_H

/** OpenGL ES versions compatible with this library. */
typedef enum SDL_GLES_Version
{
	SDL_GLES_VERSION_NONE = 0,
	/** OpenGL ES 1.1 */
	SDL_GLES_VERSION_1_1 = 1,
	/** OpenGL ES 2.0 */
	SDL_GLES_VERSION_2_0 = 2
} SDL_GLES_Version;

/** Context attributes. */
typedef enum SDL_GLES_Attr
{
	SDL_GLES_BUFFER_SIZE = 0,
	SDL_GLES_RED_SIZE,
	SDL_GLES_GREEN_SIZE,
	SDL_GLES_BLUE_SIZE,
	SDL_GLES_ALPHA_SIZE,
	SDL_GLES_LUMINANCE_SIZE,
	SDL_GLES_DEPTH_SIZE,
	SDL_GLES_STENCIL_SIZE
} SDL_GLES_Attr;

/** Represents a EGL context.
    A context is where all textures, etc. are stored.
  */
typedef struct SDL_GLES_Context
{
	/* Opaque pointer to an EGLContext */
} SDL_GLES_Context;

/** Invoke after SDL_Init.
    You need to call this before any other routine in this library.
    @param version selects the OpenGL ES version to use.
	@return 0 if SDL_gles was initialized correctly; any other value
	  if the initialization failed. You can then check for errrors using
	  SDL_GetError().
  */
int SDLCALL SDL_GLES_Init(SDL_GLES_Version version);

/** Invoke just before SDL_Quit.
    Closes the connection with the graphics accelerator. After a call to 
    SDL_GLES_Quit(), you must not call any other function in this library.
  */
void SDLCALL SDL_GLES_Quit();

/** Call before calling GetProcAddress. Dynamically loads a GLES library.
  * @param path full path to the library to load, or leave as NULL to load
  *		the default GL ES library (version as specified in SDL_GLES_Init()).
  * @return 0 if everything went OK.
  */

int SDLCALL SDL_GLES_LoadLibrary(const char *path);
/** Returns the address of a symbol in the loaded GL ES library.
  * @param proc name of the symbol to look up.
  * @return address of the symbol or NULL.
  */
void* SDLCALL SDL_GLES_GetProcAddress(const char *proc);

/** Creates a new GL ES rendering context. This is where all your textures,
  * etc. are stored. You need one for rendering; after creating it, make sure
  * it is the current one calling SDL_GLES_MakeCurrent().
  * @return the created context or NULL.
  */
SDL_GLES_Context* SDLCALL SDL_GLES_CreateContext(void);

/** Deletes an existing GL ES rendering context. This can delete the current
  * context, but after that no context will be current.
  * @param context context to delete
  */
void SDLCALL SDL_GLES_DeleteContext(SDL_GLES_Context *context);

/** Call after calling SDL_SetVideoMode() if you have an active context
  * to refresh the surface parameters.
  * @return 0 if everything went OK.
  */
int SDLCALL SDL_GLES_SetVideoMode(void);

/** Makes a context the current one. All GLES calls will use it from now on.
  * @param context context to use
  * @return 0 if everything went OK.
  */
int SDLCALL SDL_GLES_MakeCurrent(SDL_GLES_Context *context);

/** Equivalent to SDL_Flip(). Call when you're finished issuing GL calls
  * and want to draw the color buffer contents to the window surface.
  */
void SDLCALL SDL_GLES_SwapBuffers(void);

/** Sets a specific context attribute (before calling SDL_CreateContext()).
  * @param attr attribute to set
  * @param value new value
  * @return 0 if the attribute exists, -1 otherwise.
  */
int SDLCALL SDL_GLES_SetAttribute(SDL_GLES_Attr attr, int value);

/** Gets a context attribute from the current context, or from the wanted
  * attribute set if no context is current.
  * @param attr attribute to get
  * @param value pointer where the result will be stored.
  * @return 0 if the attribute exists, -1 otherwise.
  */
int SDLCALL SDL_GLES_GetAttribute(SDL_GLES_Attr attr, int *value);

#endif

