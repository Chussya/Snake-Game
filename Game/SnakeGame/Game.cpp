#include "Game.h"

#include <cassert>

#include "Record.h"
#include "GameStateMainMenu.h"
#include "GameStateLeaderboard.h"
//#include "GameStateOptions.h"
#include "GameStatePlaying.h"
#include "GameStateComplexity.h"
//#include "GameStatePause.h"
#include "GameStateGameOver.h"
//#include "GameStateExitDialog.h"

namespace SnakeGame
{
	void InitGame(Game& game)
	{
		// Generate fake records table
		InitRecord(game.records, game.gameSettings.playerName);

		game.ptrPlayerScores = &game.records[game.gameSettings.playerName];

		game.gameStateChangeType = EGameStateChangeType::None;
		game.pendingGameStateType = EGameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, EGameStateType::MainMenu);
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (game.gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(game, game.gameStateStack.back(), event);
			}
		}
	}

	bool UpdateGame(Game& game)
	{
		if (game.gameStateChangeType == EGameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		} else if (game.gameStateChangeType == EGameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (game.pendingGameStateType != EGameStateType::None && game.pendingGameStateType != EGameStateType::Exit)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType, nullptr, game.pendingGameStateIsExclusivelyVisible });
			InitGameState(game, game.gameStateStack.back());
		}

		game.gameStateChangeType = EGameStateChangeType::None;
		game.pendingGameStateType = EGameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;

		if (game.gameStateStack.size() > 0)
		{
			UpdateGameState(game, game.gameStateStack.back());
			return true;
		}
		return false;
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		if (game.gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = game.gameStateStack.rbegin(); it != game.gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(game, **it, window);
			}
		}
	}

	void ShutdownGame(Game& game)
	{
		// Shutdown all game states
		while (game.gameStateStack.size() > 0)
		{
			ShutdownGameState(game, game.gameStateStack.back());
			game.gameStateStack.pop_back();
		}

		game.gameStateChangeType = EGameStateChangeType::None;
		game.pendingGameStateType = EGameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}

	void PushGameState(Game& game, EGameStateType stateType, bool isExclusivelyVisible)
	{
		game.pendingGameStateType = stateType;
		game.pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		game.gameStateChangeType = EGameStateChangeType::Push;
	}

	void PopGameState(Game& game)
	{
		game.pendingGameStateType = EGameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = EGameStateChangeType::Pop;
	}

	void SwitchGameState(Game& game, EGameStateType newState)
	{
		game.pendingGameStateType = newState;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = EGameStateChangeType::Switch;
	}

	void InitGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case EGameStateType::MainMenu:
		{
			state.data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case EGameStateType::Complexity:
		{
			state.data = new GameStateComplexityData();
			InitGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			break;
		}
		case EGameStateType::Leaderboard:
		{
			state.data = new GameStateLeaderboardData();
			InitGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game);
			break;
		}
		case EGameStateType::Options:
		{
			//state.data = new GameStateOptionsData();
			//InitGameStateOptions(*(GameStateOptionsData*)state.data, game);
			break;
		}
		case EGameStateType::Playing:
		{
			state.data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		}
		case EGameStateType::Pause:
		{
			//state.data = new GameStatePauseData();
			//InitGameStatePause(*(GameStatePauseData*)state.data, game);
			break;
		}
		case EGameStateType::GameOver:
		{
			state.data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		case EGameStateType::ExitDialog:
		{
			//state.data = new GameStateExitDialogData();
			//InitGameStateExitDialog(*(GameStateExitDialogData*)state.data, game);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}

	void ShutdownGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case EGameStateType::MainMenu:
		{
			ShutdownGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			delete (GameStateMainMenuData*)state.data;
			break;
		}
		case EGameStateType::Complexity:
		{
			ShutdownGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			delete (GameStateComplexityData*)state.data;
			break;
		}
		case EGameStateType::Leaderboard:
		{
			ShutdownGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game);
			delete (GameStateLeaderboardData*)state.data;
			break;
		}
		case EGameStateType::Options:
		{
			//ShutdownGameStateOptions(*(GameStateOptionsData*)state.data, game);
			//delete (GameStateOptionsData*)state.data;
			break;
		}
		case EGameStateType::Playing:
		{
			ShutdownGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			delete (GameStatePlayingData*)state.data;
			break;
		}
		case EGameStateType::Pause:
		{
			//ShutdownGameStatePause(*(GameStatePauseData*)state.data, game);
			//delete (GameStatePauseData*)state.data;
			break;
		}
		case EGameStateType::GameOver:
		{
			ShutdownGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			delete (GameStateGameOverData*)state.data;
			break;
		}
		case EGameStateType::ExitDialog:
		{
			//ShutdownGameStateExitDialog(*(GameStateExitDialogData*)state.data, game);
			//delete (GameStateExitDialogData*)state.data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}

		state.data = nullptr;
	}

	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case EGameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
			break;
		}
		case EGameStateType::Complexity:
		{
			HandleGameStateComplexityWindowEvent(*(GameStateComplexityData*)state.data, game, event);
			break;
		}
		case EGameStateType::Leaderboard:
		{
			HandleGameStateLeaderboardWindowEvent(*(GameStateLeaderboardData*)state.data, game, event);
			break;
		}
		case EGameStateType::Options:
		{
			//HandleGameStateOptionsWindowEvent(*(GameStateOptionsData*)state.data, game, event);
			break;
		}
		case EGameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, game, event);
			break;
		}
		case EGameStateType::Pause:
		{
			//HandleGameStatePauseWindowEvent(*(GameStatePauseData*)state.data, game, event);
			break;
		}
		case EGameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		}
		case EGameStateType::ExitDialog:
		{
			//HandleGameStateExitDialogWindowEvent(*(GameStateExitDialogData*)state.data, game, event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}

	void UpdateGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case EGameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case EGameStateType::Complexity:
		{
			UpdateGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			break;
		}
		case EGameStateType::Leaderboard:
		{
			UpdateGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game);
			break;
		}
		case EGameStateType::Options:
		{
			//UpdateGameStateOptions(*(GameStateOptionsData*)state.data, game, timeDelta);
			break;
		}
		case EGameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		}
		case EGameStateType::Pause:
		{
			//UpdateGameStatePause(*(GameStatePauseData*)state.data, game, timeDelta);
			break;
		}
		case EGameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		case EGameStateType::ExitDialog:
		{
			//UpdateGameStateExitDialog(*(GameStateExitDialogData*)state.data, game, timeDelta);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}

	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case EGameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
			break;
		}
		case EGameStateType::Complexity:
		{
			DrawGameStateComplexity(*(GameStateComplexityData*)state.data, game, window);
			break;
		}
		case EGameStateType::Leaderboard:
		{
			DrawGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game, window);
			break;
		}
		case EGameStateType::Options:
		{
			//DrawGameStateOptions(*(GameStateOptionsData*)state.data, game, window);
			break;
		}
		case EGameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data, game, window);
			break;
		}
		case EGameStateType::Pause:
		{
			//DrawGameStatePause(*(GameStatePauseData*)state.data, game, window);
			break;
		}
		case EGameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		}
		case EGameStateType::ExitDialog:
		{
			//DrawGameStateExitDialog(*(GameStateExitDialogData*)state.data, game, window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game statee
			break;
		}
	}
}
