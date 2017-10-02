#include "FrameWork.h"
#include "MapGenerator.h"
#include "PlayState.h"
#include "Definition.h"
#include "GameStateManager.h"
#include "CreditState.h"
#include "SaveState.h"

int main(int argc, char * argv[])
{	
	
	/*	Khai báo FrameWork */
	FrameWork::fw_frameworkInitialize();

	FrameWork::Window::instance()->fww_createWindow("Guider 1911", 3, 10, 1366, 768);

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/blank.png");							// GRID
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/buttonActive.png");							// BUTTON_ACTIVE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/buttonInactive.png");						// BUTTON_NONACTIVE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/buttonHovered.png");						// BUTTON_HOVERED
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/curseur.gif");						// POINTER
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/newwoodgrain.png");							// WOOD_GRAIN
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/curseur2.gif");						// BLANK
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0119.gif");				// ROAD_HORIZONTAL
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0118.gif");				// ROAD_VERTICAL
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0124.gif");				// ROAD_CORNER_NW
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0125.gif");				// ROAD_CORNER_NE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0127.gif");				// ROAD_CORNER_WS
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0126.gif");				// ROAD_CORNER_ES
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0128.gif");				// ROAD_T_NORTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0130.gif");				// ROAD_T_WEST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0131.gif");				// ROAD_T_SOUTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0129.gif");				// ROAD_T_EAST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0134.gif");				// ROAD_END_NORTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0135.gif");				// ROAD_END_WEST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0132.gif");				// ROAD_END_SOUTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0133.gif");				// ROAD_END_EAST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0109.gif");				// ROAD_CROSSROAD
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/0101.gif");							// ROAD

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/arrowNorth.png");							// ARROW_NORTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/arrowWest.png");							// ARROW_WEST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/arrowSouth.png");							// ARROW_SOUTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/arrowEast.png");							// ARROW_EAST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/arrowNorthL.png");							// SWITCHER_NORTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/arrowWestL.png");							// SWITCHER_WEST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/arrowSouthL.png");							// SWITCHER_SOUTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/arrowEastL.png");							// SWITCHER_EAST

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/masks/quete_zone.png");				// STARTING_POINT
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/masks/pnj_zone.png");					// STARTING_POINT_ERROR
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/objects/0009.gif");					// ENDING_POINT

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/new.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/newactive.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/load.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/loadactive.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/saveactive.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/backhome.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/backhomeactive.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/leftbar.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/rightbar.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/callout.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/bitch1.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/bitch2.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/bitch3.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0006.gif");				// CONCRETE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0001.gif");				// GRASS
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0137.gif");				// GRANITE_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0138.gif");				// GRANITE_2
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0030.gif");				// BEACH_NORTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0032.gif");				// BEACH_WEST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0035.gif");				// BEACH_EAST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0036.gif");				// BEACH_SOUTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0029.gif");				// BEACH_CORNER_NW
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0031.gif");				// BEACH_CORNER_NE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0033.gif");				// BEACH_CORNER_WS
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0037.gif");				// BEACH_CORNER_ES
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0034.gif");				// SEA

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0065.gif");				//RIVER_GRASS_SOUTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0066.gif");				//RIVER_GRASS_NORTH
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0067.gif");				//RIVER_GRASS_EAST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0068.gif");				//RIVER_GRASS_WEST
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0069.gif");				//RIVER_CORNER_NE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0070.gif");				//RIVER_CORNER_NW
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0071.gif");				//RIVER_CORNER_ES
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0072.gif");				//RIVER_CORNER_WS
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0073.gif");				//GRASS_CORNER_WS
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0074.gif");				//GRASS_CORNER_NE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0075.gif");				//GRASS_CORNER_ES
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0076.gif");				//GRASS_CORNER_NW
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0090.gif");				//GRASS_SIDE_WS
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0091.gif");				//WATER_SIDE_NE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0092.gif");				//GRASS_SIDE_NE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0093.gif");				//WATER_SIDE_WS
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0094.gif");				//GRASS_SIDE_ES
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0095.gif");				//WATER_SIDE_NW
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0096.gif");				//GRASS_SIDE_NW
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0097.gif");				//WATER_SIDE_ES
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0136.gif");				//MARBLE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0089.gif");				//SAND
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/ground/0041.gif");				//SAND_GRASS

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0001.gif");				//TREE_FOUR
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0003.gif");				//TREE_ROCK_LEFT
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0004.gif");				//TREE_ROCK_RIGHT
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0005.gif");				//TREE_BIG_SMALL
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0006.gif");				//TREE_LEAFLESS
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0010.gif");				//TREE_LEAFFULL
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0011.gif");				//TREE_LEAFFULL_ROCK_SMALL
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0013.gif");				//WOOD
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0014.gif");				//TREE_WOOD
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0016.gif");				//ROCK_BIG
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0017.gif");				//ROCK_BIG_TREE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0025.gif");				//FENCE_DOUBLE_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0026.gif");				//FENCE_DOUBLE_2
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0027.gif");				//FENCE_DOUBLE_3
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0028.gif");				//FENCE_DOUBLE_4
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0029.gif");				//FENCE_SINGLE_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0030.gif");				//FENCE_SINGLE_2
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0031.gif");				//FENCE_SINGLE_3
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0032.gif");				//FENCE_DOUBLE_4
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0035.gif");				//FLOWER_UNKNOWN_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0036.gif");				//FLOWER_UNKNOWN_2
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0037.gif");				//FLOWER_UNKNOWN_3
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0038.gif");				//FLOWER_UNKNOWN_4
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0044.gif");				//FLOWER_SMALL_RED_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0052.gif");				//FLOWER_SMALL_YELLOW_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0053.gif");				//FLOWER_SMALL_RED_2
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0054.gif");				//FLOWER_SMALL_YELLOW_2
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0055.gif");				//ROCK_TWO
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0056.gif");				//TREE_COCO_LEFT
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0057.gif");				//TREE_COCO_RIGHT
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0058.gif");				//TREE_COCO_ROCK
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0060.gif");				//TREE_COCO_TWO_ROCK
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0061.gif");				//TREE_COCO_TWO
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0062.gif");				//TREE_COCO_THREE
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0066.gif");				//FLOWER_RED_FOUR
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0067.gif");				//GRASS_TALL
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0087.gif");				//TREE_LEAF_RED
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0089.gif");				//TREE_LEAF_YELLOW
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0090.gif");				//TREE_LEAF_GREEN
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0091.gif");				//TREE_UNKNOWN_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0093.gif");				//GRASS_UNKNOWN
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/world/decor/0100.gif");				//TREE_UNKNOWN_2

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/0003.gif");			// BUILDING_KEBAB
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/0007.gif");			// BUILDING_BANK_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/0019.gif");			// BUILDING_BANK_2
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/0015.gif");			// BUILDING_RESTAURANT
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/0018.gif");			// BUILDING_MOTEL
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/0020.gif");			// BUILDING_PRISON

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/newhome_1.gif");	// BUILDING_NEW_HOME_1
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/newhome_2.gif");	// BUILDING_NEW_HOME_2
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/newhome_3.gif");	// BUILDING_NEW_HOME_3
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/newhome_4.gif");	// BUILDING_NEW_HOME_4
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/newhome_5.gif");	// BUILDING_NEW_HOME_5
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/newhome_6.gif");	// BUILDING_NEW_HOME_6
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/tiles/buildings/outside/newhome_7.gif");	// BUILDING_NEW_HOME_7

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/MenuBackground.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/Campaign.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/MapGenerator.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/CustomMode.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/Credit.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/Quit.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/Instruction.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/playGame.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/CampaignButton.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/MapGeneratorButton.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/CustomModeButton.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/CreditButton.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/QuitButton.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/InstructionButton.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/playGameButton.png");
	

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/back.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/back_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/cancel.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/cancel_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/load.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/load_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/save.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/save_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/savedialog.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/textbox.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/textbox_active.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/StateLoadMap.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/prev.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/prev_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/next.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/next_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/exit.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/exit_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/non_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/instruction.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/pause.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/pause_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/resume.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/resume_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/quit.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/quit_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/newGame.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/newGame_active.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/pauseBackGround.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/playGame.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/playGameButton.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/mainMenu.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/MenuButton/mainMenu_active.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/backToMenu.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/save/backToMenu_active.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/TLP.jpg");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/moneyPlus.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/moneyMinus.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/star.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/cup.png");

	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/credit.png");
	FrameWork::TextureManager::instance()->fwtm_createTextureFromFile("image/errorStateBackground.png");

	//  load fonts
	FrameWork::FontLibrary::instance()->fwf_loadFont("font/sketchy.ttf", "sketchy large", 80);
	FrameWork::FontLibrary::instance()->fwf_loadFont("font/sketchy.ttf", "sketchy med", 20);
	FrameWork::FontLibrary::instance()->fwf_loadFont("font/solid.ttf", "solid", 20);
	FrameWork::FontLibrary::instance()->fwf_loadFont("font/solid.ttf", "solid large", 80);

	//  load sfx and music
	SoundManager::Instance()->load("sfx/mapeditor.ogg", "mapeditor", SOUND_MUSIC);
	SoundManager::Instance()->load("sfx/menu.ogg", "menu", SOUND_MUSIC);
	SoundManager::Instance()->load("sfx/play.ogg", "play", SOUND_MUSIC);
	SoundManager::Instance()->load("sfx/wrong.ogg", "wrong", SOUND_SFX);
	SoundManager::Instance()->load("sfx/click.wav", "click", SOUND_SFX);
	SoundManager::Instance()->load("sfx/right.wav", "right", SOUND_SFX);
	SoundManager::Instance()->load("sfx/timesup.wav", "timesup", SOUND_SFX);

	GameStateManager* gameStateManager = new GameStateManager();
	gameStateManager->run();

	/*	Kết thúc Frame Work	*/
	FrameWork::fw_frameworkTerminate();

	return 0;
}