#include "Game.h"

#include <cassert>

#include "Record.h"
#include "GameStateMainMenu.h"
//#include "GameStateLeaderboard.h"
//#include "GameStateOptions.h"
#include "GameStatePlaying.h"
#include "GameStateComplexity.h"
//#include "GameStatePause.h"
//#include "GameStateGameOver.h"
//#include "GameStateExitDialog.h"

namespace SnakeGame
{
	void InitGame(Game& game)
	{
		// Generate fake records table
		InitRecord(game.records);

		game.ptrPlayerScores = &game.records["Player"];

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(game, GameStateType::MainMenu);
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
		if (game.gameStateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		} else if (game.gameStateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (game.gameStateStack.size() > 0)
			{
				ShutdownGameState(game, game.gameStateStack.back());
				game.gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (game.pendingGameStateType != GameStateType::None && game.pendingGameStateType != GameStateType::Exit)
		{
			game.gameStateStack.push_back({ game.pendingGameStateType, nullptr, game.pendingGameStateIsExclusivelyVisible });
			InitGameState(game, game.gameStateStack.back());
		}

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
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

		game.gameStateChangeType = GameStateChangeType::None;
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
	}

	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible)
	{
		game.pendingGameStateType = stateType;
		game.pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		game.gameStateChangeType = GameStateChangeType::Push;
	}

	void PopGameState(Game& game)
	{
		game.pendingGameStateType = GameStateType::None;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Pop;
	}

	void SwitchGameState(Game& game, GameStateType newState)
	{
		game.pendingGameStateType = newState;
		game.pendingGameStateIsExclusivelyVisible = false;
		game.gameStateChangeType = GameStateChangeType::Switch;
	}

	void InitGameState(Game& game, GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case GameStateType::Complexity:
		{
			state.data = new GameStateComplexityData();
			InitGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			break;
		}
		case GameStateType::Leaderboard:
		{
			//state.data = new GameStateLeaderboardData();
			//InitGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game);
			break;
		}
		case GameStateType::Options:
		{
			//state.data = new GameStateOptionsData();
			//InitGameStateOptions(*(GameStateOptionsData*)state.data, game);
			break;
		}
		case GameStateType::Playing:
		{
			state.data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		}
		case GameStateType::Pause:
		{
			//state.data = new GameStatePauseData();
			//InitGameStatePause(*(GameStatePauseData*)state.data, game);
			break;
		}
		case GameStateType::GameOver:
		{
			//state.data = new GameStateGameOverData();
			//InitGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			break;
		}
		case GameStateType::ExitDialog:
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
		case GameStateType::MainMenu:
		{
			ShutdownGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			delete (GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Complexity:
		{
			ShutdownGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			delete (GameStateComplexityData*)state.data;
			break;
		}
		case GameStateType::Leaderboard:
		{
			//ShutdownGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game);
			//delete (GameStateLeaderboardData*)state.data;
			break;
		}
		case GameStateType::Options:
		{
			//ShutdownGameStateOptions(*(GameStateOptionsData*)state.data, game);
			//delete (GameStateOptionsData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			ShutdownGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			delete (GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::Pause:
		{
			//ShutdownGameStatePause(*(GameStatePauseData*)state.data, game);
			//delete (GameStatePauseData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			//ShutdownGameStateGameOver(*(GameStateGameOverData*)state.data, game);
			//delete (GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
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
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)state.data, game, event);
			break;
		}
		case GameStateType::Complexity:
		{
			HandleGameStateComplexityWindowEvent(*(GameStateComplexityData*)state.data, game, event);
			break;
		}
		case GameStateType::Leaderboard:
		{
			//HandleGameStateLeaderboardWindowEvent(*(GameStateLeaderboardData*)state.data, game, event);
			break;
		}
		case GameStateType::Options:
		{
			//HandleGameStateOptionsWindowEvent(*(GameStateOptionsData*)state.data, game, event);
			break;
		}
		case GameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)state.data, game, event);
			break;
		}
		case GameStateType::Pause:
		{
			//HandleGameStatePauseWindowEvent(*(GameStatePauseData*)state.data, game, event);
			break;
		}
		case GameStateType::GameOver:
		{
			//HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)state.data, game, event);
			break;
		}
		case GameStateType::ExitDialog:
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
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)state.data, game);
			break;
		}
		case GameStateType::Complexity:
		{
			UpdateGameStateComplexity(*(GameStateComplexityData*)state.data, game);
			break;
		}
		case GameStateType::Leaderboard:
		{
			//UpdateGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::Options:
		{
			//UpdateGameStateOptions(*(GameStateOptionsData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)state.data, game);
			break;
		}
		case GameStateType::Pause:
		{
			//UpdateGameStatePause(*(GameStatePauseData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			//UpdateGameStateGameOver(*(GameStateGameOverData*)state.data, game, timeDelta);
			break;
		}
		case GameStateType::ExitDialog:
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
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)state.data, game, window);
			break;
		}
		case GameStateType::Complexity:
		{
			DrawGameStateComplexity(*(GameStateComplexityData*)state.data, game, window);
			break;
		}
		case GameStateType::Leaderboard:
		{
			//DrawGameStateLeaderboard(*(GameStateLeaderboardData*)state.data, game, window);
			break;
		}
		case GameStateType::Options:
		{
			//DrawGameStateOptions(*(GameStateOptionsData*)state.data, game, window);
			break;
		}
		case GameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)state.data, game, window);
			break;
		}
		case GameStateType::Pause:
		{
			//DrawGameStatePause(*(GameStatePauseData*)state.data, game, window);
			break;
		}
		case GameStateType::GameOver:
		{
			//DrawGameStateGameOver(*(GameStateGameOverData*)state.data, game, window);
			break;
		}
		case GameStateType::ExitDialog:
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
