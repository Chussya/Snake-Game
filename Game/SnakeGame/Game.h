#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Record.h"
#include "GameSettings.h"

namespace SnakeGame
{
	enum class GameStateType
	{
		None = 0,
		Playing,
		Complexity,
		GameOver,
		Leaderboard,
		MainMenu,
		Options,
		Pause,
		ExitDialog,
		Exit,
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct Game
	{
		// Global data

		int* ptrPlayerScores{ nullptr };

		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameSettings gameSettings;
		std::unordered_map<std::string, int> records;
	};


	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game); // Return false if game should be closed
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	// Add new game state on top of the stack
	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);

	// Remove current game state from the stack
	void PopGameState(Game& game);

	// Remove all game states from the stack and add new one
	void SwitchGameState(Game& game, GameStateType newState);

	void InitGameState(Game& game, GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
}