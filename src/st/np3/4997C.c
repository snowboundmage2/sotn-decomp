REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    if (entity->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
REDACTED
            CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
REDACTED
REDACTED
        PlaySfxPositional(0x69C);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(D_80180AFC);
REDACTED
REDACTED
REDACTED
REDACTED
        xDistance = GetDistanceToPlayerX();
        yDistance = GetDistanceToPlayerY();
        if ((xDistance < 96) && (yDistance < 96) && !(GetSideToPlayer() & 2)) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity(D_80182570, entity) == 0) {
            entity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            entity->velocityY = FIX(0.875);
            if (entity->facingLeft != 0) {
                entity->velocityX = FIX(0.25);
REDACTED
                entity->velocityX = FIX(-0.25);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_80182554, entity);
REDACTED
        if (GetDistanceToPlayerY() < 0x20) {
            if (entity->facingLeft == 0) {
                entity->velocityX = FIX(-1);
REDACTED
                entity->velocityX = FIX(1);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        AnimateEntity(D_80182554, entity);
REDACTED
        if ((u32)(entity->velocityY + 0x10000) > 0x20000U) {
REDACTED
REDACTED
REDACTED
        entity->velocityY += *(s32*)&entity->ext.generic.unk7C.u;
REDACTED
REDACTED
REDACTED
