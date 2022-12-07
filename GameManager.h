#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
#include "PlayerBody.h"


class GameManager {
private:
	/// These are called "forward declarations" The idea is that a pointer is 
	/// really just an unsigned int, so to create a pointer to it you really only
	/// need to tell the compiler that there is a class called Window and I need
	/// a pointer to it, thus the "class Window*" means trust me, there is a class 
	/// called Window, I just need a pointer to it.

	/// If that was too much for your brain, just #include "Window.h" and declare
	/// Window *ptr and don't use the word "class"  This is a second semester C++
	/// topic anyway
	class Window *windowPtr;
	class Timer *timer;
	bool isRunning;
	class Scene *currentScene;
    class PlayerBody *player;
    Uint32 changeSceneEventType; // event type number for user defined events
    bool launched = true;

public:
	GameManager();
	~GameManager();
	bool OnCreate();
	void OnDestroy();
	float getSceneHeight();
	float getSceneWidth();
	Matrix4 getProjectionMatrix();
    PlayerBody* getPlayer(){ return player; }
	Uint32 getChangeScene() { return changeSceneEventType; }

	SDL_Renderer* getRenderer();
	void RenderPlayer(float scale = 1.0f);
	void Run();
    void LoadScene( int i );
    void handleEvents();
    bool ValidateCurrentScene();
    
};
#endif


