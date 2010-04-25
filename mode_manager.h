
#ifndef __MODE_MANAGER_HEADER__
#define __MODE_MANAGER_HEADER__

#include "utils.h"
#include "defs.h"

namespace hoa_mode_manager {

extern ModeEngine* ModeManager;

extern bool MODE_MANAGER_DEBUG;

const uint8 MODE_MANAGER_DUMMY_MODE  = 0;
const uint8 MODE_MANAGER_BOOT_MODE   = 1;
const uint8 MODE_MANAGER_MAP_MODE    = 2;
const uint8 MODE_MANAGER_BATTLE_MODE = 3;
const uint8 MODE_MANAGER_MENU_MODE   = 4;
const uint8 MODE_MANAGER_SHOP_MODE   = 5;
const uint8 MODE_MANAGER_PAUSE_MODE  = 6;
const uint8 MODE_MANAGER_SCENE_MODE  = 7;
const uint8 MODE_MANAGER_WORLD_MODE  = 8;
const uint8 MODE_MANAGER_SAVE_MODE   = 9;

class GameMode {
	friend class ModeEngine;
public:
	GameMode();

	GameMode(uint8 mt);

	virtual ~GameMode();

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void Reset() = 0;
};

class ModeEngine : public hoa_utils::Singleton<ModeEngine> {
private:
	ModeEngine();

	std::vector<GameMode*> _game_stack;

	std::vector<GameMode*> _push_stack;

	bool _state_change;

	uint32 _pop_count;

public:
	~ModeEngine();

	bool SingletonInitialize();

	void Pop();

	void PopAll();

	void Push(GameMode* gm);

	GameMode* GetTop();

	GameMode* Get(uint32 index);

	void Update();

	void Draw();

	void DEBUG_PrintStack();
};

#endif
