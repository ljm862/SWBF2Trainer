#include "includes.h"

void Hack::GetEntityList() {
	for (int i = 0; i < 64; i++)
	{
		ListOfEntities[i] = (ListedEntities*)((uintptr_t)EntityList + (0x1B0 * i));
	}
}

Entity* Hack::GetLocalPlayer() {
	uintptr_t entity = (uintptr_t)ListOfEntities[0]->PlayersEntity;
	return entity < 0x100 ? localPlayer : (Entity*)(entity - 0x240);
}

void Hack::Init()
{
	moduleBase = (uintptr_t)GetModuleHandleW(L"BattlefrontII.exe");
	EntityList = *(ListedEntities**)(moduleBase + EntityListOffset);
	GetEntityList(); // Will need to re-get this at start of every new map
	localPlayer = GetLocalPlayer();
}

void Hack::Update() {
	memcpy(&viewMatrix, (PBYTE*)(moduleBase + viewMatrixOffset), sizeof(viewMatrix));
}

bool Hack::CheckValidEnt(Entity* entity) {
	if (entity == nullptr || (uintptr_t)entity == (uintptr_t)0xFFFFFDC0 || entity->MaxHealth == NULL ||
		entity == localPlayer || entity->CurrentHealth <= 0) {
		return false;
	}
	else {
		return true;
	}
}

bool Hack::WorldToScreen(Vector3 pos, Vector2& screen) {
	Vector4 clipcoords;
	clipcoords.x = pos.x * viewMatrix[0] + pos.y * viewMatrix[1] + pos.z * viewMatrix[2] + viewMatrix[3];
	clipcoords.y = pos.x * viewMatrix[4] + pos.y * viewMatrix[5] + pos.z * viewMatrix[6] + viewMatrix[7];
	clipcoords.z = pos.x * viewMatrix[8] + pos.y * viewMatrix[9] + pos.z * viewMatrix[10] + viewMatrix[11];
	clipcoords.w = pos.x * viewMatrix[12] + pos.y * viewMatrix[13] + pos.z * viewMatrix[14] + viewMatrix[15];

	if (clipcoords.w < 0.1f) return false;

	Vector3 NDC;
	NDC.x = clipcoords.x / clipcoords.w;
	NDC.y = clipcoords.y / clipcoords.w;
	NDC.z = clipcoords.z / clipcoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

bool Hack::AnotherWorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3* pos, D3DXVECTOR3* out) {
	D3DVIEWPORT9 viewPort;
	D3DXMATRIX view, projection, world;
	pDevice->GetViewport(&viewPort);
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	D3DXMatrixIdentity(&world);

	D3DXVec3Project(out, pos, &viewPort, &projection, &view, &world);
	if (out->z < 1) {
		return true;
	}
	return false;
}