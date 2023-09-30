#ifndef __DUNGEON_H_
#define __DUNGEON_H_

#include "DungeonRoom.h"

using namespace SDLFramework;

class Dungeon : public GameEntity {
private:
	InputManager* mInput;

	static const int DUNGEON_ROWS = 3;
	static const int DUNGEON_COLUMNS = 3;
	DungeonRoom* mCurrentRoom;
	DungeonRoom* mDungeonMap[DUNGEON_ROWS][DUNGEON_COLUMNS];
	int mDungeonLayout[DUNGEON_ROWS][DUNGEON_COLUMNS] = {
		{1, 1, 0},
		{0, 1, 1},
		{1, 1, 1}
	};

public:
	Dungeon();
	~Dungeon();

	void Update() override;
	void Render() override;
private:
	void CreateDoorConnections();
	void MoveToRoom(DungeonRoom::Direction direction);

};

#endif //__DUNGEON_H_