#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"
#include "Constants.h"
#include "UtilGraphic.h"

namespace SnakeGame
{
	template<typename F>
	struct MenuItem
	{
		bool onFocus{ false };
		sf::Text text;
		F callFunc;
	};

	template<typename F>
	bool operator==(const MenuItem<F>& a, const MenuItem<F>& b)
	{
		return a.text.getString() == b.text.getString();
	}

	template<typename F>
	void InitMenuItem(MenuItem<F>& menuItem, const std::string text, const sf::Font& font, const unsigned int charSize, F callFunc)
	{
		InitText(menuItem.text, text, font, sf::Color::White, charSize);
		menuItem.text.setOutlineColor(sf::Color::Green);
		menuItem.callFunc = callFunc;
	}

	template<typename F>
	void DrawMenuItem(MenuItem<F>& menuItem, sf::RenderWindow& window)
	{
		window.draw(menuItem.text);
	}

	template<typename F>
	void OnFocus(MenuItem<F>& menuItem)
	{
		menuItem.onFocus = true;

		menuItem.text.setOutlineThickness(2);
	}

	template<typename F>
	void LostFocus(MenuItem<F>& menuItem)
	{
		menuItem.onFocus = false;

		menuItem.text.setOutlineThickness(0);
	}

	void EditElement(std::string& playerName, sf::Font& font);
}