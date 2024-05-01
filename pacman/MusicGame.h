#ifndef MUSIC_GAME_H_
#define MUSIC_GAME_H_

#include "CommonFunction.h"

class MusicGame
{
public:
	MusicGame();
	~MusicGame();

	void loadMusic();

	Mix_Music* getMusicBackground() const;

	Mix_Chunk* getMusicEatDot() const;
	Mix_Chunk* getMusicEatBigDot() const;
	Mix_Chunk* getMusicDie() const;
	Mix_Chunk* getWinGame() const;
	Mix_Chunk* getMusicTimeOut() const;
	Mix_Chunk* getMusicLiveOut() const;
	Mix_Chunk* getMusicStartGame() const;
	void free();
private:

	Mix_Music* music_background_;

	Mix_Chunk* music_eat_dot_;
	Mix_Chunk* music_eat_big_dot_;
	Mix_Chunk* music_die_;
	Mix_Chunk* music_win_game_;
	Mix_Chunk* music_time_out_;
	Mix_Chunk* music_live_out_;
	Mix_Chunk* music_start_game_;
};

#endif // !MUSIC_GAME_H_

