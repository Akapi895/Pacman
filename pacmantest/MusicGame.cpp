#include "MusicGame.h"

MusicGame::MusicGame() {
    music_background_ = NULL;
	music_eat_dot_ = NULL;
	music_eat_big_dot_ = NULL;
	music_die_ = NULL;
	music_win_game_ = NULL;
	music_time_out_ = NULL;
	music_live_out_ = NULL;
	music_start_game_ = NULL;
}

MusicGame::~MusicGame() {
    freeResources();
}

bool MusicGame::loadMusic() {
    bool success = true;

    success &= loadMusicFile("music/music_background.mp3", &music_background_);
    success &= loadChunkFile("music/music_eat_dot.wav", &music_eat_dot_);
    success &= loadChunkFile("music/music_eat_big_dot.wav", &music_eat_big_dot_);
    success &= loadChunkFile("music/music_die.wav", &music_die_);
    success &= loadChunkFile("music/music_win_game.wav", &music_win_game_);
    success &= loadChunkFile("music/music_time_out.wav", &music_time_out_);
    success &= loadChunkFile("music/music_time_out.wav", &music_live_out_);
    success &= (bool) (music_start_game_  = Mix_LoadWAV("music/music_start_game.mp3"));

    return success;
}

Mix_Music* MusicGame::getMusicBackground() const {
	return music_background_;
}

Mix_Chunk* MusicGame::getMusicEatDot() const {
	return music_eat_dot_;
}

Mix_Chunk* MusicGame::getMusicEatBigDot() const {
	return music_eat_big_dot_;
}

Mix_Chunk* MusicGame::getMusicDie() const {
	return music_die_;
}

Mix_Chunk* MusicGame::getWinGame() const {
	return music_win_game_;
}

Mix_Chunk* MusicGame::getMusicTimeOut() const {
	return music_time_out_;
}

Mix_Chunk* MusicGame::getMusicLiveOut() const {
	return music_live_out_;
}

Mix_Chunk* MusicGame::getMusicStartGame() const {
	return music_start_game_;
}

void MusicGame::freeResources() {
    Mix_FreeChunk(music_eat_dot_);
	Mix_FreeChunk(music_eat_big_dot_);
	Mix_FreeChunk(music_die_);
	Mix_FreeChunk(music_win_game_);
	Mix_FreeChunk(music_time_out_);
	Mix_FreeChunk(music_live_out_);
	Mix_FreeChunk(music_start_game_);
    Mix_FreeMusic(music_background_);

	music_eat_dot_ = NULL;
	music_eat_big_dot_ = NULL;
	music_die_ = NULL;
	music_win_game_ = NULL;
	music_time_out_ = NULL;
	music_live_out_ = NULL;
	music_start_game_ = NULL;
	music_background_ = NULL;

	Mix_Quit();
}

bool MusicGame::loadMusicFile(const std::string& filePath, Mix_Music** musicPtr) {
  *musicPtr = Mix_LoadMUS(filePath.c_str());
  if (*musicPtr == nullptr) {
    std::cerr << "Error loading music: " << filePath << " - " << Mix_GetError() << std::endl;
    return false;
  }
  return true;
}
bool MusicGame::loadChunkFile(const std::string& filePath, Mix_Chunk** musicPtr) {
  *musicPtr = Mix_LoadWAV(filePath.c_str());
  if (*musicPtr == nullptr) {
    std::cerr << "Error loading music: " << filePath << " - " << Mix_GetError() << std::endl;
    return false;
  }
  return true;
}
