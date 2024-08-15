#ifndef WEAPON_PRIVATE_H
#define WEAPON_PRIVATE_H

#include "weapon_common.h"

// exported
static void EntityWeaponAttack(Entity* self);
static void LoadWeaponPalette(s32 clutIndex);
static s32 func_ptr_80170004(Entity* self);
static void func_ptr_80170008(Entity* self);
static void func_ptr_8017000C(Entity* self);
static s32 func_ptr_80170010(Entity* self);
static s32 func_ptr_80170014(Entity* self);
static int GetWeaponId(void);
static void EntityWeaponShieldSpell(Entity* self);
static void func_ptr_80170024(Entity* self);
static void func_ptr_80170028(Entity* self);
static void WeaponUnused2C(void);
static void WeaponUnused30(void);
static void WeaponUnused34(void);
static void WeaponUnused38(void);
static void WeaponUnused3C(void);

void DestroyEntity(Entity* entity);
static void SetSpriteBank1(SpriteParts* animset);
static void SetSpriteBank2(SpriteParts* animset);
static void DecelerateX(s32 amount);
static void DecelerateY(s32 amount);
static void SetSpeedX(s32 speed);

Weapon OVL_EXPORT(header) = {
    EntityWeaponAttack, func_ptr_80170004, func_ptr_80170008,
    func_ptr_8017000C,  func_ptr_80170010, func_ptr_80170014,
    GetWeaponId,        LoadWeaponPalette, EntityWeaponShieldSpell,
    func_ptr_80170024,  func_ptr_80170028, WeaponUnused2C,
    WeaponUnused30,     WeaponUnused34,    WeaponUnused38,
    WeaponUnused3C,
};

#endif
