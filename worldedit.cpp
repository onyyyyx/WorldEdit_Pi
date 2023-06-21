#include <libreborn/libreborn.h>
#include <symbols/minecraft.h>
#include <mods/misc/misc.h>

typedef unsigned char uchar;

#define DEBUG_STICK_ID 450

static Level_getTile_t Level_getData = (Level_getTile_t) 0xa3324;

static int debugStick_useOn(uchar *item, ItemInstance *item_instance, uchar *player, uchar *level, int32_t x, int32_t y, int32_t z, int32_t hit_side, float hit_x, float hit_y, float hit_z) {
    // Change the id
    int id = (*Level_getTile)(level, x, y, z);
    int data = (*Level_getData)(level, x, y, z);
    data = (data + 1) % 0xF;
    (*Level_setTileAndData)(level, x, y, z, id, data);
    return 1;
}

static void Tile_initTiles_injection(__attribute__((unused)) uchar *null) {
    // Allocate
    uchar *debugStick = (uchar *) ::operator new(ITEM_VTABLE_SIZE);
    ALLOC_CHECK(debugStick);

    // Construct
    (*Item)(debugStick, DEBUG_STICK_ID - 256);

    // Copy Old VTable
    uchar *vtable = (uchar *) malloc(ITEM_VTABLE_SIZE);
    ALLOC_CHECK(vtable);
    memcpy((void *) vtable, (void *) Item_vtable, ITEM_VTABLE_SIZE);
    *(uchar **) debugStick = vtable;

    // Get functions
    Item_setIcon_t Item_setIcon = *(Item_setIcon_t *) (vtable + Item_setIcon_vtable_offset);
    Item_setDescriptionId_t Item_setDescriptionId = *(Item_setDescriptionId_t *) (vtable + Item_setDescriptionId_vtable_offset);

    // Setup
    (*Item_setIcon)(debugStick, 5, 3);
    (*Item_setDescriptionId)(debugStick, "debugStick");

    // Overwrite functions
    *(Item_useOn_t *) (vtable + Item_useOn_vtable_offset) = debugStick_useOn;
}

// Add debugStick to creative inventory
static void Inventory_setupDefault_FillingContainer_addItem_call_injection(uchar *filling_container) {
    ItemInstance *debugStickBlock_instance = new ItemInstance;
    ALLOC_CHECK(debugStickBlock_instance);
    debugStickBlock_instance->count = 255;
    debugStickBlock_instance->auxiliary = 0;
    debugStickBlock_instance->id = DEBUG_STICK_ID;
    (*FillingContainer_addItem)(filling_container, debugStickBlock_instance);
}

__attribute__((constructor)) static void init() {
    misc_run_on_tiles_setup(Tile_initTiles_injection);
    misc_run_on_creative_inventory_setup(Inventory_setupDefault_FillingContainer_addItem_call_injection);
}
