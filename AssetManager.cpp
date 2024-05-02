#include "AssetManager.h"
#include <iostream>

void AssetManager::LoadTexture(std::string name, std::string file_name)
{
    sf::Texture tex;

    if (tex.loadFromFile(file_name))
    {
        this->_textures[name] = std::move(tex);
    }
    else
    {
        std::cerr << "Failed to load texture: " << file_name << std::endl;
    }
}

sf::Texture& AssetManager::GetTexture(std::string name)
{
    auto it = this->_textures.find(name);
    if (it != this->_textures.end())
    {
        return it->second;
    }
    else
    {
        std::cerr << "Texture not found: " << name << std::endl;
        // Return a reference to a default texture or handle the error in some other way
        // Note: Returning a reference to a temporary local object would be unsafe!
        //       Ensure that the returned reference always refers to a valid texture.
        // Example:
        static sf::Texture emptyTexture; // Default texture
        return emptyTexture;
    }
}

void AssetManager::LoadFont(std::string name, std::string file_name)
{
    sf::Font font;

    if (font.loadFromFile(file_name))
    {
        this->_fonts[name] = std::move(font);
    }
    else
    {
        std::cerr << "Failed to load font: " << file_name << std::endl;
    }
}

sf::Font& AssetManager::GetFont(std::string name)
{
    auto it = this->_fonts.find(name);
    if (it != this->_fonts.end())
    {
        return it->second;
    }
    else
    {
        std::cerr << "Font not found: " << name << std::endl;
        // Return a reference to a default font or handle the error in some other way
        // Note: Returning a reference to a temporary local object would be unsafe!
        //       Ensure that the returned reference always refers to a valid font.
        // Example:
        static sf::Font emptyFont; // Default font
        return emptyFont;
    }
}
