#include <vector>

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a,b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}



class CommandPost
{
public:
	union {
		DEFINE_MEMBER_N(wchar_t*, Name, 0x0028);
	};
};

class PlayerEntity
{
public:
	union
	{
		DEFINE_MEMBER_N(uintptr_t*, UseThisPointersAddressMinus244, 0x4);
	};

}; //Size: 0x09F0

class WeaponVariables
{
public:
	union {
		DEFINE_MEMBER_N(float, AmmoDecrementer, 0x4);
		DEFINE_MEMBER_N(float, OverheatChange, 0xc);
		DEFINE_MEMBER_N(float, OverheatLimit, 0x10);
	};
};

class EntityClass
{
public:
	union {
		DEFINE_MEMBER_N(wchar_t*, ClassName, 0x0020);
	};
}; //Size: 0x0404

class WeaponData
{
public:
	WeaponVariables* WeaponVars;
	union {
		DEFINE_MEMBER_N(float, MaxTotalAmmo, 0x8);
		DEFINE_MEMBER_N(float, ReserveAmmo, 0xc);
		DEFINE_MEMBER_N(float, InWeaponAmmo, 0x10);
	};
};

class WeaponInformation
{
public:
	union {
		DEFINE_MEMBER_N(uint32_t, WeaponState, 0x00B0);
		DEFINE_MEMBER_N(WeaponData*, DataOfWeapon, 0x88);
		DEFINE_MEMBER_N(float, OverheatTimerMaybe, 0x120);
	};
}; //Size: 0x0104

class WeaponClass
{
public:
	union {
		DEFINE_MEMBER_N(wchar_t*, WeaponName, 0x0050);
	};
}; //Size: 0x00C4

class Team
{
public:
	DEFINE_MEMBER_N(wchar_t*, TeamName, 0x000C);
	DEFINE_MEMBER_N(uint32_t, RemainingTickets, 0x0028);
	DEFINE_MEMBER_N(uint32_t, TotalTickets, 0x002C);

	wchar_t* NamePrefix2; //0x0098
	wchar_t* NamePrefix3; //0x009C
	wchar_t* NamePrefix4; //0x00A0
	wchar_t* NamePrefix5; //0x00A4
	wchar_t* NamePrefix6; //0x00A8
	wchar_t* NamePrefix7; //0x00AC
	wchar_t* NamePrefix8; //0x00B0
	wchar_t* NamePrefix9; //0x00B4
	wchar_t* NamePrefix10; //0x00B8
	wchar_t* NamePrefix11; //0x00BC
	wchar_t* NamePrefix12; //0x00C0
	wchar_t* NamePrefix13; //0x00C4
	wchar_t* NamePrefix14; //0x00C8
	wchar_t* NamePrefix15; //0x00CC
	wchar_t* NamePrefix16; //0x00D0
	wchar_t* NamePrefix17; //0x00D4
	wchar_t* NamePrefix18; //0x00D8
	wchar_t* NamePrefix19; //0x00DC
	wchar_t* NamePrefix20; //0x00E0
	wchar_t* NamePrefix21; //0x00E4
	wchar_t* NamePrefix22; //0x00E8
	wchar_t* NamePrefix23; //0x00EC
	wchar_t* NamePrefix24; //0x00F0
	wchar_t* NamePrefix25; //0x00F4
};

class PlayerInfo
{
public:
	union {
		//DEFINE_MEMBER_N(WeaponInformation*, CurrentWeaponInfo, 0x0000);
		DEFINE_MEMBER_N(WeaponClass*, CurrentWeaponClass, 0x0004);
		DEFINE_MEMBER_N(float, TotalAmmo, 0x000C);
		DEFINE_MEMBER_N(float, MagazineAmmo, 0x0010);
		DEFINE_MEMBER_N(WeaponInformation*, GrenadeInformation, 0x0028);
		DEFINE_MEMBER_N(WeaponClass*, GrenadeClass, 0x002C);
		DEFINE_MEMBER_N(float, OwnerHP, 0x0074);
		DEFINE_MEMBER_N(float, OwnerStamina, 0x008C);
	};
}; //Size: 0x053C

class ListedEntities
{
public:
	union {
		DEFINE_MEMBER_N(wchar_t, Name[64], 0x0030);
		DEFINE_MEMBER_N(wchar_t, NameAgain[64], 0x00B0);
		DEFINE_MEMBER_N(Team*, PlayerTeam, 0x0138);
		DEFINE_MEMBER_N(EntityClass*, PlayerEntityClass, 0x0140);
		DEFINE_MEMBER_N(PlayerEntity*, PlayersEntity, 0x0148);
	};
}; //Size: 0x01B0

class PlayerInformation
{
public:
	union {
		// LinkedList of entities
		//DEFINE_MEMBER_N(Entity*, EntityBefore, 0x0010);
		//DEFINE_MEMBER_N(Entity*, EntityAfter, 0x0014);

		DEFINE_MEMBER_N(wchar_t, Name[16], 0x0030);
		DEFINE_MEMBER_N(wchar_t, NameAgain[16], 0x00B0);
		DEFINE_MEMBER_N(Team*, PlayerTeam, 0x0138);

		// There seems to be a list of command posts in the class.
		//class CommandPost* N000010C1; //0x0198
	};
}; //Size: 0x043C

class Entity
{
public:

	union {
		DEFINE_MEMBER_N(EntityClass*, CharacterClass, 0x0008);
		DEFINE_MEMBER_N(Vector3, BodyCoordinates, 0x7C);
		DEFINE_MEMBER_N(float, CurrentHealth, 0x0144);
		DEFINE_MEMBER_N(float, MaxHealth, 0x0148);
		DEFINE_MEMBER_N(PlayerInformation*, Player, 0x030C);
		DEFINE_MEMBER_N(WeaponInformation*, PrimaryWeaponInfo, 0x708);
		DEFINE_MEMBER_N(WeaponInformation*, WeaponInventory[6], 0x720);
		DEFINE_MEMBER_N(uint32_t, CurrentWeaponID, 0x0740);
		DEFINE_MEMBER_N(float, Stamina, 0xA14);
	};


	//class N00000A5A* VisibleEntities; //0x0010 This is some kind of datastructure, needs further investigating
	class N00000346* N0000029F; //0x0050
	class N000008E9* N000002A7; //0x008C

	// All these vectors are various things. Body, head, gun, camera, and probably more. Unsure as to what any of them are for now
	Vector3 HeadCoordinates; //0x0018
	Vector3 N000002A3; //0x0060
	Vector3 N000002A4; //0x006C
	Vector3 N000002B0; //0x00AC
	Vector3 N000002B4; //0x00C4
	Vector4 N000002BD; //0x00F0
	Vector4 N000002C3; //0x0110
	Vector3 N000002C4; //0x0120

	void* GameModel; //0x0130

	// Two controller classes for moving around depending on what this character is
	//class AIControl* AIControl; //0x02DC
	//class PlayerControl* PlayerControl; //0x0308

	/*virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();*/
}; //Size: 0x0C10
