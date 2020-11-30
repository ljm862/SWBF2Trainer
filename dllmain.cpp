#include "includes.h"
#pragma warning(disable : 4996)

struct Variables {
	bool bHealth = false;
	bool bStamina = false;
	bool bAmmo = false;
	bool bAimbot = false;
	bool bWalls = false;
} val;

void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene oEndScene = nullptr;
extern LPDIRECT3DDEVICE9 pDevice = nullptr;
Hack* hack;

void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice) {
	if (!pDevice) pDevice = o_pDevice;

	for (auto entity : hack->ListOfEntities)
	{
		Entity* trueEnt = (Entity*)((uintptr_t)(entity->PlayersEntity) - 0x240);
		if (entity->PlayersEntity == 0 || !hack->CheckValidEnt(trueEnt)) {
			continue;
		}

		D3DCOLOR color;
		if (trueEnt->Player->PlayerTeam->TeamName == hack->localPlayer->Player->PlayerTeam->TeamName) {
			color = D3DCOLOR_ARGB(255, 0, 255, 0);
		}
		else {
			color = D3DCOLOR_ARGB(255, 255, 0, 0);
		}

		/*Vector2 entPos2D;
		if (hack->WorldToScreen(trueEnt->BodyCoordinates, entPos2D)) {
			DrawLine(entPos2D.x, entPos2D.y, windowWidth / 2, windowHeight, 2, color);
		}*/
		D3DXVECTOR3 entPos2D;// = new D3DXVECTOR3(hack->localPlayer->BodyCoordinates.x, hack->localPlayer->BodyCoordinates.y, hack->localPlayer->BodyCoordinates.z);;
		D3DXVECTOR3* inputPos = new D3DXVECTOR3(trueEnt->BodyCoordinates.x, trueEnt->BodyCoordinates.y, trueEnt->BodyCoordinates.z);
		if (hack->AnotherWorldToScreen(pDevice, inputPos, &entPos2D)) {
			DrawLine(entPos2D.x, entPos2D.y, windowWidth / 2, windowHeight, 2, color);
		}
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
		val.bHealth = !val.bHealth;
	}

	if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
		val.bStamina = !val.bStamina;
	}

	if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
		val.bAmmo = !val.bAmmo;
	}

	hack->localPlayer = hack->GetLocalPlayer();

	if (val.bHealth) {
		hack->localPlayer->CurrentHealth = 1000;
	}

	if (val.bStamina) {
		hack->localPlayer->Stamina = 120;
	}

	if (val.bAmmo) {
		// Crashes when becoming droideka. Those things have WEIRD setup so need to investigate 
		for (auto weapon : hack->localPlayer->WeaponInventory) {
			if (weapon != NULL) {
				weapon->DataOfWeapon->MaxTotalAmmo < 5 ?
					weapon->DataOfWeapon->WeaponVars->AmmoDecrementer = 0 :
					weapon->DataOfWeapon->WeaponVars->OverheatChange = weapon->DataOfWeapon->WeaponVars->OverheatLimit;
			}
		}
	}

	oEndScene(pDevice);
}

DWORD WINAPI HackThread(HMODULE hModule) {

	/*
	Goodbye sweet console, it's time to move onto gui now. You shall be missed
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);*/

	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		memcpy(EndSceneBytes, (BYTE*)d3d9Device[42], 7);
		oEndScene = (tEndScene)mem::TrampolineHook32((BYTE*)d3d9Device[42], (BYTE*)hkEndScene, 7);
	}

	hack = new Hack();
	hack->Init();

	while (!GetAsyncKeyState(VK_END)) {
		hack->Update();
	}

	mem::Patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);

	Sleep(1000);

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, 0));
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

