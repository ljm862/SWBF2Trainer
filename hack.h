class Hack {
public:
	uintptr_t EntityListOffset = 0x1A30334;
	uintptr_t viewMatrixOffset = 0x4EED20;
	uintptr_t CameraManagerOffset = 0x1A30324; // But then it's dereferenced I think

	uintptr_t moduleBase = NULL;
	Entity* localPlayer = NULL;
	ListedEntities* EntityList = NULL;
	ListedEntities* ListOfEntities[64];
	float viewMatrix[16];

	ID3DXLine* LineL;
	LPD3DXFONT FontF;

	void Init();
	void Update();
	bool CheckValidEnt(Entity* entity);
	bool WorldToScreen(Vector3 pos, Vector2& screen);
	bool AnotherWorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3* pos, D3DXVECTOR3* out);
	void GetEntityList();
	Entity* GetLocalPlayer();
};