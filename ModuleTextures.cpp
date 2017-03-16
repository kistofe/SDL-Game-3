#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
	for (int i = 0; i < MAX_TEXTURES; i++) { textures[i] = nullptr; }
	// TODO 5: Initialize all texture pointers to nullptr
}

// Destructor
ModuleTextures::~ModuleTextures()
{}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}


	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (int i = 0; i <= last_texture; i++) { SDL_DestroyTexture(textures[i]); }
	// TODO 6: Free all textures

	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Texture* test_texture = nullptr;
	SDL_Surface* test_image = IMG_Load(path);
	if (test_image == nullptr)
	{
		LOG("Failed to load image at %s", path);
	}
	// TODO 2: Load and image from a path (must be a png)
	// and check for errors

	else
	{
		test_texture = SDL_CreateTextureFromSurface(App->render->renderer, test_image);

		if (test_texture == nullptr) { LOG("Failed to create texture from %s", path); }
	}
	// TODO 3: Once your have the SDL_surface*, you need to create
	// a texture from it to return it (check for errors again)
	SDL_FreeSurface(test_image);

	textures[last_texture++] = test_texture;
	if (last_texture >= MAX_TEXTURES)
	{
		LOG("Texture overflow");
		last_texture = 0;
	}
	// TODO 4: Before leaving, remember to free the surface and
	// add the texture to our own array so we can properly free them

	return test_texture;
}
