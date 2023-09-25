#include "TunnelBlock.h"

int TunnelBlock::sTunnelSpacing = TUNNEL_SPACING;

TunnelBlock::TunnelBlock() {
	mTimer = Timer::Instance();

	mRoofBlock = new Block();
	mRoofBlock->Parent(this);
	mRoofBlock->Position(Vector2(0.0f, -sTunnelSpacing));

	mFloorBlock = new Block();
	mFloorBlock->Parent(this);
	mFloorBlock->Position(Vector2(0.0f, sTunnelSpacing));
}
TunnelBlock::~TunnelBlock() {
	delete mRoofBlock;
	mRoofBlock = nullptr;

	delete mFloorBlock;
	mFloorBlock = nullptr;

	mTimer = nullptr;
}

int TunnelBlock::GetSpacing(){
	return sTunnelSpacing;
}
void TunnelBlock::PrintSpacing() const{
	std::cout << "TunnelBlock Spacing: " << sTunnelSpacing << std::endl;
}

void TunnelBlock::Update() {

}
void TunnelBlock::Render() {
	mRoofBlock->Render();
	mFloorBlock->Render();
}

void TunnelBlock::NewGame() {
	sTunnelSpacing = TUNNEL_SPACING;
}
void TunnelBlock::DecreaseBlockSpacing() {
	sTunnelSpacing--;
}


