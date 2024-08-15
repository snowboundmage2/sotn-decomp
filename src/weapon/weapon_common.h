#ifndef WEAPON_COMMON_H
#define WEAPON_COMMON_H

#include <weapon.h>

#define WEAPON0 // forces WEAPON0 for the time being

#if defined(WEAPON0)
#define HAND_ID 0
#elif defined(WEAPON1)
#define HAND_ID 1
#else
#warning "WEAPON0 or WEAPON1 not specified. Falling back to WEAPON0."
#define HAND_ID 0
#endif

// create function names like w_000_EntityWeaponAttack
#ifdef VERSION_PC
#define CONCATENATE_DETAIL(x, y, z) x##y##_##z
#define CONCATENATE(x, y, z) CONCATENATE_DETAIL(x, y, z)
#define OVL_EXPORT(x) CONCATENATE(WEAPON, WEAPON_ID, x)
#else
#define OVL_EXPORT(x) x
#endif

#endif
