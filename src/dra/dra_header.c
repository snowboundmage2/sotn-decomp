// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

typedef void (*Entrypoint)(void);

extern EnemyDef g_EnemyDefs[];
extern Equipment g_EquipDefs[];
extern Accessory g_AccessoryDefs[];
extern RelicDesc g_RelicDefs[];

void MainGame(void);
void FreePrimitives(s32 primitiveIndex);
s32 AllocPrimRecursively(u8 primType, s32 count);
void CheckCollision(s32 x, s32 y, Collider* res, s32 unk);
void InitializeBackbufferCoords(s32 start);
u32 UpdateAnim(s8* frameProps, AnimationFrame** anims);
void SetSpeedX(s32 speed);
Entity* GetFreeEntity(s16 start, s16 end);
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId);
s32 InitClutAnimation(u32 arg0);
void LoadGfxAsync(s32 gfxId);
void PlaySfx(s16 sfxId);
s32 AllocatePrimitives(u8 primType, s32 count);
void ResetClutAnimation(s32 arg0);
void SetBackgroundColor(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
void UpdatePrimState(u32 arg0);
void TransformPolygon(
    s16 pivotX, s16 pivotY, Entity* e, u16 flags, POLY_GT4* p, u8 flipX);
Entity* CreateEntFactoryFromEntity(Entity* source, u32 flags, s16 arg2);
bool IsSoundPlaying(void);
DR_ENV* AllocateDrawEnvironment(POLY_GT4* poly);
u16* func_80106A28(u32 arg0, u16 kind);
void AssignEntityEnemyId(Entity* self);
Entity* FindActiveEntity(void);
s16 CalculateEntityAngle(Entity* ent1, Entity* ent2, s16 facingLeft);
u32 UpdateUnarmedAnim(s8* frameProps, u16** frames);
void PlayAnimation(s32*, AnimationFrame** frames);
void SetBackgroundColorTimer(s32 arg0);
void SetPlayerBlinkTimer(s32 arg0, s16 arg1);
void ResetAfterImage(s32 resetAnims, s32 arg1);
u16 DealDamage(Entity* enemyEntity, Entity* attackerEntity);
void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index);
void AddHearts(s32 value);
bool LoadMonsterLibrarianPreview(s32 monsterId);
s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action);
void ResetAfterImageCounter(void);
s32 UpdatePlayerStats(s32 amount, s32 type);
void AddToInventory(u16 itemId, s32 itemCategory);
void InitStatsAndGear(bool isDeathTakingItems);
u32 PlaySfxVolPan(s16 sfxId, s32 sfxVol, u16 sfxPan);
s32 SetVolumeCommand22_23(s16 vol, s16 distance);
void UpdatePlayerAttributes(void);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void GetPlayerSensor(Collider* col);
void func_800F1FC4(s32 arg0);
void func_800F2288(void); // unknown signature
void GetServantStats(Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
s32 CalculateLuckAdjustedValue(s32 arg0);
s32 DetermineItemDrop(EnemyDef* arg0);
bool CdSoundCommandQueueEmpty(void);
bool func_80133950(void);
bool func_800F27F4(s32 arg0);
s32 GetStatBuffTimer(s32 arg0);
s32 AdjustForInvertedCastle(s32 arg0);
bool CalcPlayerDamage(DamageParam* arg0);
void LearnSpell(s32 spellId);
void DebugInputWait(const char* msg);

Entrypoint g_MainGame = MainGame;
GameApi g_ApiInit = {
    {},
    FreePrimitives,
    AllocPrimRecursively,
    CheckCollision,
    InitializeBackbufferCoords,
    UpdateAnim,
    SetSpeedX,
    GetFreeEntity,
    GetEquipProperties,
    InitClutAnimation,
    LoadGfxAsync,
    PlaySfx,
    AllocatePrimitives,
    ResetClutAnimation,
    SetBackgroundColor,
    UpdatePrimState,
    TransformPolygon,
    CreateEntFactoryFromEntity,
    IsSoundPlaying,
    AllocateDrawEnvironment,
    func_80106A28,
    AssignEntityEnemyId,
    g_EnemyDefs,
    FindActiveEntity,
    CalculateEntityAngle,
    UpdateUnarmedAnim,
    PlayAnimation,
    SetBackgroundColorTimer,
    SetPlayerBlinkTimer,
    ResetAfterImage,
    DealDamage,
    LoadEquipIcon,
    g_EquipDefs,
    g_AccessoryDefs,
    AddHearts,
    LoadMonsterLibrarianPreview,
    TimeAttackController,
    ResetAfterImageCounter,
    UpdatePlayerStats,
    AddToInventory,
    g_RelicDefs,
    InitStatsAndGear,
    PlaySfxVolPan,
    SetVolumeCommand22_23,
    UpdatePlayerAttributes,
    CheckEquipmentItemCount,
    GetPlayerSensor,
    func_800F1FC4,
    func_800F2288,
    GetServantStats,
    CalculateLuckAdjustedValue,
    DetermineItemDrop,
    CdSoundCommandQueueEmpty,
    func_80133950,
    func_800F27F4,
    GetStatBuffTimer,
    AdjustForInvertedCastle,
    CalcPlayerDamage,
    LearnSpell,
    DebugInputWait,
};
