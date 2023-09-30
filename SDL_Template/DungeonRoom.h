#ifndef __DUNGEON_ROOM_H_
#define __DUNGEON_ROOM_H_

#include "InputManager.h"
#include "GameEntity.h"
#include "GLTexture.h"
#include <map>

using namespace SDLFramework;

class DungeonRoom : public GameEntity {
public:
	enum class Direction { NONE = -1, UP, RIGHT, DOWN, LEFT };
private:
	static const float X_LEFT_BOUNDARY;
	static const float X_RIGHT_BOUNDARY;
	static const float Y_TOP_BOUNDARY;
	static const float Y_BOTTOM_BOUNDARY;

	InputManager* mInput;

	GLTexture* mBackground;

	// map of exits?
	std::map<DungeonRoom::Direction, DungeonRoom*> mDoors; // would not be bool, but a reference to another room (DungeonRoom*)
	std::map<DungeonRoom::Direction, GLTexture*> mDoorTextures;
public:
	DungeonRoom();
	~DungeonRoom();

	void AddDoor(DungeonRoom::Direction direction, DungeonRoom* connectedRoom);
	DungeonRoom* GetDoor(DungeonRoom::Direction direction);

	void Update() override;
	void Render() override;

private:
	void CreateDoorTextures();
};

#endif //__DUNGEON_ROOM_H_
