#include "textureHolder.hpp"
#include <assert.h>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename) {
	// Get a reference to m_Texture using m_s_Instance
	auto& m = m_s_Instance->m_Textures;

	// Create an iterator and search m for the passed filename
	auto keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		// if found return the texture
		return keyValuePair->second;
	} // if
	else {
		// Create a new key value pair using the filename
		auto& texture = m[filename];
		// load the tetxture from file into map besides its filename
		texture.loadFromFile(filename);

		return texture;
	} // else
} // GetTexture function
