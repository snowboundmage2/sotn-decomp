#include "np3.h"
#include "sfx.h"

// The enemy called "Blade", his helper functions, and his swords

static void func_801D0A00(s16* arg0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
static void func_801D0B40(void) {
    s16* unk88 = g_CurrentEntity[15].ext.et_801D0B40.unk88;
    g_CurrentEntity[15].ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;

    unk88 = g_CurrentEntity[16].ext.et_801D0B40.unk88;
    g_CurrentEntity[16].ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;
}
REDACTED
// Function does not use the argument, but all calls in EntityBlade
// give one, so we include it here.
static s32 func_801D0B78(Entity* unused) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (g_CurrentEntity->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
void EntityBlade(Entity* self) {
    Collider collider;
    Entity* otherEnt;
    Entity* var_s3;
    s16* var_s2;
    s16* var_s4;
    s32 var_v0;
    u16 zPriority;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(0xE);
    }
    if ((self->flags & 0x100) && (self->step < 0x18U) &&
        (((self + 13)->ext.GH_Props.unk88 != 0) ||
         ((self + 10)->ext.GH_Props.unk88 != 0))) {
        PlaySfxPositional(0x750);
        func_801CE1E8(0x18);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BBC);
        self->animCurFrame = 0;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->facingLeft = self->params;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_801833E4) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
REDACTED
    case 2:
        var_s3 = self;
        for (var_s4 = &D_801833F4; *var_s4 != 0; var_s4 += 5) {
            otherEnt = self + var_s4[0];
            CreateEntityFromCurrentEntity(E_GURKHA_BODY_PARTS, otherEnt);
            otherEnt->ext.GH_Props.unk9E = var_s4[2];
            otherEnt->ext.GH_Props.parent = self + var_s4[1];
            otherEnt->params = var_s4[3] + 0x200;
            zPriority = self->zPriority + var_s4[4];
            otherEnt->unk60 = var_s3;
            var_s3 = otherEnt;
            var_s3->unk5C = self;
            var_s3->zPriority = zPriority;
        }
        self->unk60 = var_s3;
        self->unk5C = NULL;

        otherEnt = self + 15;
        CreateEntityFromCurrentEntity(E_BLADE_SWORD, otherEnt);
        otherEnt->ext.GH_Props.unk9E = 12;
        otherEnt->ext.GH_Props.parent = self + 5;
        otherEnt->zPriority = self->zPriority + 3;
        otherEnt->params = 19;

        otherEnt = self + 16;
        CreateEntityFromCurrentEntity(E_BLADE_SWORD, otherEnt);
        otherEnt->ext.GH_Props.unk9E = 12;
        otherEnt->ext.GH_Props.parent = self + 8;
        otherEnt->zPriority = self->zPriority - 4;
        otherEnt->params = 19;
        self->step++;
        /* fallthrough */
    case 3:
        func_801CE228();
        func_801CE1E8(5);
        /* fallthrough */
    case 5:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80183530;
        } else {
            var_s2 = D_80183548;
        }
        func_801CDF1C(var_s2, &D_80183600, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801D0B40();
        func_801CE258(&D_80183494);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = &self[var_s2[3]];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                self->ext.GH_Props.unk88 =
                    func_801CE120(otherEnt, self->facingLeft);
                var_v0 = func_801D0B78(otherEnt);
                if (var_v0) {
                    func_801CE1E8(var_v0);
                }
            }
        }
        break;
    case 7:
        if (self->step_s == 0) {
            self->ext.GH_Props.unkB0[0] = 1;
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80183560;
        } else {
            var_s2 = D_80183570;
        }
        func_801CDF1C(var_s2, &D_80183638, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801D0B40();
        func_801CE258(&D_80183494);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = &self[var_s2[3]];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                if (func_801CE120(otherEnt, self->facingLeft ^ 1) != 0) {
                    func_801CE1E8(6);
                }
                self->ext.GH_Props.unk88 =
                    func_801CE120(otherEnt, self->facingLeft);
                var_v0 = func_801D0B78(self);
                if (var_v0) {
                    func_801CE1E8(var_v0);
                }
            }
        }
        break;
    case 6:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80183530;
        } else {
            var_s2 = D_80183548;
        }
REDACTED
REDACTED
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_801834B8;
            } else {
                var_s2 = D_801834D8;
            }
            func_801CDF1C(var_s2, &D_801838C4, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801D0B40();
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                self->step_s++;
            }
            self->step_s++;
            break;
        case 1:
            func_801CDF1C(var_s2, &D_80183700, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801D0B40();
            if ((self->ext.GH_Props.unkB0[2] == 0) &&
                (self->ext.GH_Props.unkB0[0] == 0)) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->velocityY = FIX(-1);
            func_801CE228();
            self->step_s++;
            /* fallthrough */
        case 3:
REDACTED
            self->velocityY += FIX(11.0 / 128);
            func_801CDF1C(var_s2, &D_80183720, 0);
            func_801CDE10(var_s2);
            func_801CE3FC(var_s2);
            func_801D0B40();
            otherEnt = &self[var_s2[3]];
            collider.unk18 = 9;
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                self->ext.GH_Props.unk88 =
                    func_801CE120(otherEnt, self->facingLeft);
                var_v0 = func_801D0B78(otherEnt);
                if (var_v0 != 0) {
                    func_801CE1E8(var_v0);
                } else {
                    self->step_s = 1;
                }
            }
            break;
        }
        func_801CE258(&D_80183494);
        break;
    case 8:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_801834B8;
        } else {
            var_s2 = D_801834D8;
        }
        switch (self->step_s) {
        case 0:
            (self + 15)->ext.GH_Props.unk8D = 1;
            (self + 16)->ext.GH_Props.unk8D = 1;
            self->ext.GH_Props.unk8D = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_801CDF1C(var_s2, &D_8018386C, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801CE258(&D_80183494);
            if ((self + 16)->hitFlags) {
                self->ext.GH_Props.unk8D = 1;
            }
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                if (self->ext.GH_Props.unk8D != 0) {
                    self->step_s = 3;
                } else {
                    self->step_s = 2;
                }
            }
            break;
        case 2:
            func_801CDF1C(var_s2, &D_8018389C, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            if ((self->ext.GH_Props.unkB0[0] == 1) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_C);
            }
            func_801CE258(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                (self + 15)->ext.GH_Props.unk8D = 0;
                (self + 16)->ext.GH_Props.unk8D = 0;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(var_s2, &D_801835A8, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801CE258(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                var_v0 = func_801D0B78(self);
                if (var_v0 != 0) {
                    func_801CE1E8(var_v0);
                } else {
                    func_801CE1E8(5);
                }
            }
            break;
        }
        break;
    case 10:
        if (self->step_s == 0) {
            PlaySfxPositional(0x74E);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_801834F8;
        } else {
            var_s2 = D_80183514;
        }
        func_801CDF1C(var_s2, &D_80183934, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801D0B40();
        func_801CE258(&D_80183494);
        otherEnt = self + var_s2[5];
        otherEnt->ext.GH_Props.unk8D = 1;
        if ((self->ext.GH_Props.unkB0[0] == 0) &&
            (self->ext.GH_Props.unkB0[2] == 0)) {
            otherEnt =
                self + var_s2[5]; // repeated line, surprised it gets compiled
            otherEnt->ext.GH_Props.unk8D = 0;
            var_v0 = func_801D0B78(self);
            if (var_v0 != 0) {
                func_801CE1E8(var_v0);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 12:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80183530;
        } else {
            var_s2 = D_80183548;
        }
        func_801CDF1C(var_s2, &D_80183760, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801D0B40();
        func_801CE258(&D_80183494);
        if (self->ext.GH_Props.unkB0[2] == 0) {
            self->ext.GH_Props.unk88 = 0;
            self->facingLeft ^= 1;
            var_v0 = func_801D0B78(self);
            if (var_v0 != 0) {
                func_801CE1E8(var_v0);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 14:
        if (self->step_s == 0) {
            PlaySfxPositional(0x74F);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_801834B8;
        } else {
            var_s2 = D_801834D8;
        }
        func_801CDF1C(var_s2, &D_80183990, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801CE258(&D_80183494);
        if ((self->ext.GH_Props.unkB0[0] == 0) &&
            (self->ext.GH_Props.unkB0[2] == 0)) {
            var_v0 = func_801D0B78(self);
            if (var_v0 != 0) {
                func_801CE1E8(var_v0);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 24:
        switch (self->step_s) {
        case 0:
            for (var_s2 = &D_80183494; *var_s2 != 0; var_s2++) {
                otherEnt = self + *var_s2;
                otherEnt->hitboxState = 0;
            }
            self->hitboxState = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_801834B8;
            } else {
                var_s2 = D_801834D8;
            }
            func_801CDF1C(var_s2, &D_80183A24, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801CE258(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 3) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                PlaySfxPositional(SFX_STOMP_HARD_A);
            }
            if (self->ext.GH_Props.unkB0[0] == 0 &&
                self->ext.GH_Props.unkB0[2] == 0) {
                self->step_s++;
            }
REDACTED
        case 2:
            var_s2 = D_80183580;
            func_801CDF1C(var_s2, &D_80183A4C, 0);
            func_801CDE88(var_s2);
            func_801CE258(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB0[2] == 0)) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
                (self + 15)->ext.GH_Props.unk8C = 1;
                (self + 15)->ext.GH_Props.rotZ = 0x400;
                (self + 15)->rotZ = 0x400;
                self->ext.GH_Props.unk80 = 0x20;
                self->step_s++;
            }
            break;
        case 3:
            if (--self->ext.GH_Props.unk80 == 0) {
                self->step_s++;
            }
            break;
        case 4:
            for (var_s2 = &D_80183494; *var_s2 != 0; var_s2++) {
                otherEnt = self + *var_s2;
                otherEnt->step = 0x18;
                otherEnt->step_s = 0;
            }
            self->ext.GH_Props.unk80 = 0x40;
            self->step_s++;
            /* fallthrough */
        case 5:
            if (!(g_Timer & 7)) {
                if (Random() & 1) {
                    PlaySfxPositional(SFX_FM_EXPLODE_B);
                } else {
                    PlaySfxPositional(SFX_EXPLODE_D);
                }
            }
            if (--self->ext.GH_Props.unk80 == 0) {
                DestroyEntity(self);
            }
            return;
        }
        break;
    }
    for (var_s2 = &D_80183494; *var_s2 != 0; var_s2++) {
        otherEnt = self + *var_s2;
        otherEnt->facingLeft = self->facingLeft;
        otherEnt->ext.GH_Props.unkA8 = 0;
REDACTED
    D_8006C384.y = self->ext.GH_Props.unkB0[0];
    D_8006C38C.y = self->ext.GH_Props.unkB0[2];
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->drawFlags |= 4;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            prim->drawMode = 0x33;
REDACTED
REDACTED
REDACTED
        self->rotZ = self->ext.et_801D1BB8.unk9C;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (self->facingLeft == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    angle = self->rotZ;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                prim->drawMode = 0x33;
REDACTED
                prim->drawMode = 0xA;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    angle = self->rotZ;
    if (self->facingLeft != 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 0x33;
REDACTED
        prim->drawMode = 0xA;
REDACTED
REDACTED
