#include "Common.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "Functions.hpp"


namespace Big::selfFunctions {

    // Self Options

    void neverWanted(bool enable)
    {
        if (enable)
        {
            PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_PED_ID(), 0, false);
            PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_PED_ID(), false);
            PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_PED_ID(), true);
            PLAYER::SET_MAX_WANTED_LEVEL(0);
        }
        else
        {
            PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_PED_ID(), false);
            PLAYER::SET_MAX_WANTED_LEVEL(5);
        }
    }
    void godMode(bool enable)
    {
        if (enable)
        {
            PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
        }
        else {
            PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
        }
    }
}

namespace Big::weaponFunctions
{

    Hash weapons[] = { 0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0xA2719263, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, 0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0xA3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D, 0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94,0x84D6FAFD, 0x624FE830, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, 0x5FC3C11, 0xC472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, 0xB1CA77B1, 0xA284510B, 0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x781FE4A, 0xB62D1F67, 0x93E220BD, 0xA0973D5E, 0xFDBC8A50, 0x497FACC3, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0x34A67B97, 0x60EC506, 0xFBAB5776, 0xBA536372 };

    void getAllWeapons()
    {

        for (Hash weapon : weapons)
        {
            if (!WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), weapon, false))
            {
                WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), weapon, 200, false);
            }
        }
    }

    void setMaxAmmo()
    {
        for (Hash weapon : weapons)
        {
            if (WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), weapon, false))
            {
                int maxAmmo = 0;
                WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), weapon, &maxAmmo);
                WEAPON::SET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), weapon, WEAPON::GET_MAX_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), weapon, false));
                WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), weapon, maxAmmo, false);
            }
        }
    }

    void giveParachute()
    {
        if (!WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, false))
        {
            WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 200, false);
        }
    }

    void setInfiniteAmmo(bool enable)
    {
        if (enable)
        {
            WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true);
        } 
        else 
        {
            WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), false);
        }
    }
}

namespace Big::vehicleFunctions
{
    // TODO: Fix this mudda fucka 
    void spawnVehicle(const char* modelName)
    {
        DWORD model = MISC::GET_HASH_KEY(modelName);
        if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
        {
            STREAMING::REQUEST_MODEL(model);
            while (!STREAMING::HAS_MODEL_LOADED(model))
            {
                g_Logger->Info("Waiting...");
            }
            NativeVector3 position = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 6.0, 0.5);
            Vehicle vehicle = VEHICLE::CREATE_VEHICLE(model, position.x, position.y, position.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, true, true);
            VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, true);

            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
            ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehicle);

            g_Logger->Info("Spawned Vehicle");
        } 
        else
        {
            g_Logger->Info("Vehicle doesn't exist");
        }
    }

}

namespace Big::teleportFunctions
{
    NativeVector3 getBlipMarker()
    {
        static NativeVector3 zero;
        NativeVector3 coords;
        bool blipFound = false;

        int blipIterator = HUD::_GET_BLIP_INFO_ID_ITERATOR();
        for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(blipIterator); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(blipIterator))
        {
            if (HUD::GET_BLIP_INFO_ID_TYPE(i) == 4) // 4 is waypoint blip 
            {
                coords = HUD::GET_BLIP_INFO_ID_COORD(i);
                blipFound = true;
                break;
            }
        }
        if (blipFound)
        {
            return coords;
        }

        return zero;
    }

    void teleportToCoords(Entity Player, NativeVector3 coords)
    {
        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Player, coords.x, coords.y, coords.z, 0, 0, 1);
    }

    void teleportToWaypoint()
    {
        NativeVector3 coords = getBlipMarker();

        if (coords.x == 0 && coords.y == 0)
        {
            g_Logger->Info("No Waypoint has been set!");
            return;
        }

        Entity Player = PLAYER::PLAYER_PED_ID();
        if (PED::IS_PED_IN_ANY_VEHICLE(Player, false))
        {
            Player = PED::GET_VEHICLE_PED_IS_USING(Player);
        }

        bool groundFound = false;
        static float checkGroundHeight[] = { 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };

        for (int i = 0; i < sizeof(checkGroundHeight) / sizeof(float); i++)
        {
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Player, coords.x, coords.y, checkGroundHeight[i], 0, 0, 1);
            Sleep(100);
            if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, checkGroundHeight[i], &coords.z, 0))
            {
                groundFound = true;
                coords.z += 3.0;
                break;
            }
        }

        if (!groundFound)
        {
            coords.z = 1000.0;
            WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 200, false);
        }

        teleportToCoords(Player, coords);
    }
}