#ifndef __TUNNEL_BLOCK_H
#define __TUNNEL_BLOCK_H
#include "Block.h"

using namespace SDLFramework;

class TunnelBlock : public GameEntity {
private:

	// Need to find the lower limit for TUNNEL_SPACING so game doesn't break
	static const int TUNNEL_SPACING = 560;
	static int sTunnelSpacing;

	Timer* mTimer;

	Block* mRoofBlock;
	Block* mFloorBlock;

public:
	TunnelBlock();
	~TunnelBlock();

	static int GetSpacing();
	void PrintSpacing() const;

	void Update() override;
	void Render() override;

	static void NewGame();
	static void DecreaseBlockSpacing();
};
#endif
