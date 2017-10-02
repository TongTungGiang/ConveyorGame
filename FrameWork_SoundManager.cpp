//#include "FrameWork.h"
//
//using FrameWork::SoundManager;
//
//SoundManager* SoundManager::singleton = NULL;
//
//void SoundManager::fwsm_initialize()
//{
//	if (Mix_OpenAudio(22050, AUDIO_S16, 2, 4096) == -1)
//		exit(EXIT_FAILURE);
//
//}
//
//void SoundManager::fwsm_destroy()
//{
//	Mix_CloseAudio();
//	delete singleton;
//}
//
//bool SoundManager::fwsm_load(std::string fileName, std::string id, sound_type type)
//{
//	if (type == SOUND_MUSIC)
//	{
//		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
//
//		if (pMusic == 0)
//		{
//			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
//			return false;
//		}
//		music[id] = pMusic;
//		return true;
//	}
//	else if (type == SOUND_SFX)
//	{
//		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
//		if (pChunk == 0)
//		{
//			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
//			return false;
//		}
//		sfxs[id] = pChunk;
//		return true;
//	}
//	return false;
//}
//
//void SoundManager::fwsm_playMusic(std::string id, int loop)
//{
//	Mix_PlayMusic(music[id], loop);
//}
//
//void SoundManager::fwsm_playSound(std::string id, int loop)
//{
//	Mix_PlayChannel(-1, sfxs[id], loop);
//}
//
