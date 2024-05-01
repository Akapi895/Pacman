#include "MusicGame.h"

MusicGame::MusicGame()
{
	music_background_ = NULL;

	music_eat_dot_ = NULL;
	music_eat_big_dot_ = NULL;
	music_die_ = NULL;
	music_win_game_ = NULL;
	music_time_out_ = NULL;
	music_live_out_ = NULL;

}

MusicGame::~MusicGame()
{
	free();
}

void MusicGame::loadMusic()
{
	music_background_ = Mix_LoadMUS("music_/music_background.wav");
	
	
	music_eat_dot_ = Mix_LoadWAV("music_/music_eat_dot.wav");
	music_eat_big_dot_ = Mix_LoadWAV("music_/music_eat_big_dot.wav");
	music_die_ = Mix_LoadWAV("music_/music_die.wav");
	music_win_game_ = Mix_LoadWAV("music_/music_win_game.wav");
	music_time_out_ = Mix_LoadWAV("music_/music_time_out.wav");
	music_live_out_ = Mix_LoadWAV("music_/music_live_out.wav");
	music_start_game_ = Mix_LoadWAV("music_/music_start_game.wav");
}

Mix_Music* MusicGame::getMusicBackground() const
{
	return music_background_;
}

Mix_Chunk* MusicGame::getMusicEatDot() const
{
	return music_eat_dot_;
}

Mix_Chunk* MusicGame::getMusicEatBigDot() const
{
	return music_eat_big_dot_;
}

Mix_Chunk* MusicGame::getMusicDie() const
{
	return music_die_;
}

Mix_Chunk* MusicGame::getWinGame() const
{
	return music_win_game_;
}

Mix_Chunk* MusicGame::getMusicTimeOut() const
{
	return music_time_out_;
}

Mix_Chunk* MusicGame::getMusicLiveOut() const
{
	return music_live_out_;
}

Mix_Chunk* MusicGame::getMusicStartGame() const
{
	return music_start_game_;
}

void MusicGame::free()
{
	Mix_FreeChunk(music_eat_dot_);
	Mix_FreeChunk(music_eat_big_dot_);
	Mix_FreeChunk(music_die_);
	Mix_FreeChunk(music_win_game_);
	Mix_FreeChunk(music_time_out_);
	Mix_FreeChunk(music_live_out_);
	Mix_FreeChunk(music_start_game_);

	music_eat_dot_ = NULL;
	music_eat_big_dot_ = NULL;
	music_die_ = NULL;
	music_win_game_ = NULL;
	music_time_out_ = NULL;
	music_live_out_ = NULL;
	music_start_game_ = NULL;

	Mix_FreeMusic(music_background_);
	music_background_ = NULL;

	Mix_Quit();
}
