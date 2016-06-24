#ifndef SETTINGS_HPP__

# define SETTINGS_HPP__

#include <string>

class Settings
{
public:
	static unsigned int SizeTextLegendRessources;
	static unsigned int SizeTextLegendPlayer;
	/* broadcast */
	static unsigned int SizeBroadCast;
	static unsigned int SpeedBroadcast;
	/* incantation */
	static unsigned int RotationMaxIncantation;
	static unsigned int SpeedIncantation;
	/* root */
	static unsigned int AntiAliasing;
	static unsigned int WindowSizeX;
	static unsigned int WindowSizeY;
	static unsigned int FPS;
	static std::string  WindowTitle;
	/* panel time */
	static unsigned int BeginPanelTimeY;
	static unsigned int TimePitch;
	/* panel teams */
	static unsigned int PanelTeamX;
	static unsigned int PanelSizeY;
	static unsigned int PanelTeamSizeBlocPlayer;
	static unsigned int PanelTeamPlayerDisplayed;
	/* map */
	static unsigned int CoeffRessources;
};

#endif // EOF - Settings.hpp