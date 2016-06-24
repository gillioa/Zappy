#include <iostream>

#include "TextureManager.hpp"
#include "Except.hpp"

TextureManager TextureManager::m_instance = TextureManager();

TextureManager::TextureManager()
{
	/* sprites */
	for (auto &i : TEXTURES_PATH)
	{
		sf::Texture current_texture;

		std::cout << "[TextureManager] -> loading : " << i.first << std::endl;
		if (!current_texture.loadFromFile(i.first))
		{
			std::cerr << "[TextureManager] failed" << std::endl;
			throw Except("Error : [TextureManager] failed to load :" + i.first);
		}
		current_texture.setSmooth(true);
		m_textures[i.second] = current_texture;
	}
	/* font */
	if (!m_font.loadFromFile("./assets/Animated.ttf"))
	{
		std::cerr << "[TextureManager] failed" << std::endl;
		throw Except("Error : [TextureManager] failed to load Animated.ttf" );
	}
}

TextureManager::~TextureManager() {}

TextureManager& TextureManager::Instance() { return m_instance; }

const sf::Texture & TextureManager::getTexture(const e_texture id) { return m_textures[id]; }
const sf::Font    & TextureManager::getFont () { return m_font; }