#include "Common.hpp"

namespace Big::selfFunctions
{
	void neverWanted(bool enable);
	void godMode(bool enable);

	
}

namespace Big::weaponFunctions
{
	void getAllWeapons();
	void setMaxAmmo();
	void giveParachute();
	void setInfiniteAmmo(bool enable);
}

namespace Big::vehicleFunctions
{
	void spawnVehicle(const char* modelName);
}

namespace Big::teleportFunctions
{
	 void teleportToWaypoint();
}