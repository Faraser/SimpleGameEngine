#include "AudioEngine.h"
#include "EngineErrors.h"

namespace Engine {

void SoundEffect::play(int loops /* = 0 */) {
    if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
        if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
            fatalError("Mix PlayChannel error: " + std::string(Mix_GetError()));
        }
    };
}

void Music::play(int loops /* = 1 */) {
    if (Mix_PlayMusic(m_music, loops) == -1) {
        fatalError("Mix PlayMusic error: " + std::string(Mix_GetError()));
    };
}

void Music::pause() {
    Mix_PauseMusic();
}

void Music::stop() {
    Mix_HaltMusic();
}

void Music::resume() {
    Mix_ResumeMusic();
}

AudioEngine::~AudioEngine() {
    destroy();
}

void AudioEngine::init() {
    if (m_isInitialized) {
        fatalError("Try to initialize Audio Engine twice");
    }

    // Parameters can be a bitwise combination of MIX_INIT_FAC
    // MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
        fatalError("Mix Init error: " + std::string(Mix_GetError()));
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        fatalError("Mix open audio error: " + std::string(Mix_GetError()));
    }

    m_isInitialized = true;
}

void AudioEngine::destroy() {
    if (m_isInitialized) {
        m_isInitialized = false;

        for (const auto& effect: m_effectMap) {
            Mix_FreeChunk(effect.second);
        }

        for (const auto& music: m_musicMap) {
            Mix_FreeMusic(music.second);
        }

        m_effectMap.clear();
        m_musicMap.clear();

        Mix_Quit();
    }
}

SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
    SoundEffect effect;

    // Try to find the audio in the cache
    auto it = m_effectMap.find(filePath);

    if (it == m_effectMap.end()) {
        // Failed to find it, must load
        Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
        if (chunk == nullptr) {
            fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
        }

        effect.m_chunk = chunk;
        m_effectMap[filePath] = chunk;
    } else {
        effect.m_chunk = it->second;
    }

    return effect;
}

Music AudioEngine::loadMusic(const std::string& filePath) {
    Music music;

    // Try to find the audio in the cache
    auto it = m_musicMap.find(filePath);

    if (it == m_musicMap.end()) {
        // Failed to find it, must load
        Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
        if (mixMusic == nullptr) {
            fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
        }

        music.m_music = mixMusic;
        m_musicMap[filePath] = mixMusic;
    } else {
        music.m_music = it->second;
    }

    return music;
}

}