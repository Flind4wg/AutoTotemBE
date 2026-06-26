#include <jni.h>
#include <string>

class Player;
class ItemStack;

void (*Player_tick)(Player* self);
ItemStack* (*Player_getOffhandSlot)(Player* self);
bool (*ItemStack_isAir)(ItemStack* self);
int (*ItemStack_getDescriptorId)(ItemStack* self);
void (*Player_setOffhandSlot)(Player* self, ItemStack* item);
ItemStack* (*Inventory_getItem)(Player* self, int slot);
void (*Inventory_setItem)(Player* self, int slot, ItemStack* item);

const int TOTEM_ID = 562; 

void hook_Player_tick(Player* self) {
    Player_tick(self);

    if (!self) return;

    ItemStack* offhandItem = Player_getOffhandSlot(self);
    
    if (!offhandItem || ItemStack_isAir(offhandItem) || ItemStack_getDescriptorId(offhandItem) != TOTEM_ID) {
        for (int i = 0; i < 36; i++) {
            ItemStack* currentItem = Inventory_getItem(self, i);
            
            if (currentItem && ItemStack_getDescriptorId(currentItem) == TOTEM_ID) {
                Player_setOffhandSlot(self, currentItem);
                ItemStack* emptyItem = nullptr; 
                Inventory_setItem(self, i, emptyItem);
                break; 
            }
        }
    }
}

