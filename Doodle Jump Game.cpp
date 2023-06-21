#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <random>
#include "Framework.h"

//using namespace std;

// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
// > > > > > > >        GLOBALS        < < < < < < < //
// | | | | | | | \ . . . . . . . . . / | | | | | | | //
int screen_width, screen_height;
int	&w = screen_width, &h = screen_height;
int doodle_position_x, doodle_position_y;
int item_position_x, item_position_y;
int cursor_position_x, cursor_position_y;

int platform_width = 90, platform_height = 24;
int doodle_width = 90, doodle_height = 90;
int item_width = 28, item_height = 24;
int digit_width = 28, digit_height = 33;
int monster_width = 82, monster_height = 52;
int play_button_width = 222, play_button_height = 80;
int cursor_width = 32, cursor_height = 32;
int coin_width = 32, coin_height = 32;
int projectile_length = 14;
int counting_score = 0;
int spring_boots_time = 0;
int doodle_jump_h;
int game_over_screen_y;
int projectail_speed = 10;
int numberOfPlatforms = 100;
int numberOfMonsters = 10;
int numberOfProjectiles = 100;
int numberOfCoins = 10;
int px, py;

bool title_screen = true;
bool gameStarted = false;
bool gameOver = false;
bool item_spawned = false;
bool mouse_on_play_button = false;
bool doodle_has_spring_boots = false;
bool doodle_left_movement = false, doodle_right_movement = false;
bool mouse_left_click = false, mouse_right_click = false;
bool game_title_screen_animation = true;       // true - after title screen | false - after game over screen

float falling_speed = 0;

FRKey which_key_is_pressed;

// ----------------------------------------------------
//     GLOBALS for Limiting Frame Rate System (FPS) 
const int FPS = 60;
const int frameDelay = 1000 / FPS;
unsigned int frameStart;
int frameTime;
// ----------------------------------------------------


// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
// > > > > > > >        TEXTURES       < < < < < < < //
// | | | | | | | \ . . . . . . . . . / | | | | | | | //

	// Prepare background textures
	const char* backgroundTextures[] = {
	"data/DustyBackground.png",                // 0
	"data/GroundBackground.png",               // 1
	"data/DustyBackground.png"                 // 2
};

	// Prepare doodle textures
	const char* doodleClassicTextures[] = {
		"data/blue-lik-left@2x.png",           // 0
		"data/blue-lik-left-odskok@2x.png",    // 1
		"data/blue-lik-puca@2x.png",           // 2
		"data/blue-lik-puca-odskok@2x.png",    // 3
		"data/blue-lik-right@2x.png",          // 4
		"data/blue-lik-right-odskok@2x.png"    // 5
	};

	// Prepare game textures
	const char* gameTextures[] = {
		"data/game-tiles@2x.png"               // 0
	};

	// Prepare platform textures
	const char* platformTextures[] = {
		"data/green-platform.png",             // 0
		"data/fake-platform.png",              // 1
		"data/fake-platform-breaking1.png",    // 2
		"data/fake-platform-breaking2.png",    // 3
		"data/fake-platform-breaking3.png",    // 4
		"data/fake-platform-breaking4.png"     // 5
	};

	// Prepare spring boots textures
	const char* springBootsTextures[] = {
		"data/spring-boots1-left.png",         // 0
		"data/spring-boots2-left.png",         // 1
		"data/spring-boots3-left.png",         // 2
		"data/spring-boots1-right.png",        // 3
		"data/spring-boots2-right.png",        // 4
		"data/spring-boots3-right.png"         // 5
	};

	// Prepare spring boots textures
	const char* itemTextures[] = {
		"data/item-spring-boots.png"           // 0
	};

	const char* digitTextures[] = {
		"data/number-0.png",				   // 0
		"data/number-1.png",				   // 1
		"data/number-2.png",			 	   // 2
		"data/number-3.png",			 	   // 3
		"data/number-4.png",				   // 4
		"data/number-5.png",				   // 5
		"data/number-6.png",				   // 6
		"data/number-7.png",				   // 7
		"data/number-8.png",				   // 8
		"data/number-9.png"					   // 9
	};

	// Prepare top and bottom bar textures
	const char* barTextures[] = {
		"data/dark-top-score.png",             // 0
		"data/bottom-bar.png"                  // 1
	};

	// Prepare play button textures
	const char* playButtonTextures[] = {
		"data/play@2x.png",					   // 0
		"data/play-on@2x.png",				   // 1
		"data/play-on.png",					   // 2
		"data/play-again.png",				   // 3
		"data/play-again-on@2x.png"		       // 4
	};

	// Prepare header text textures
	const char* headerTextures[] = {
		"data/header-doodle-jump.png",		   // 0
		"data/header-game-over.png" 		   // 1
	};

	// Prepare score texts textures
	const char* textTextures[] = {
		"data/header-doodle-jump.png",		   // 0
		"data/header-game-over.png",		   // 1
		"data/your-score-high-score.png"       // 2
	};

	// Prepare monster textures
	const char* monsterTextures[] = {
		"data/monster.png",		               // 0
		"data/monster-dead.png"                // 1
	};

	// Prepare projectile textures
	const char* projectileTextures[] = {
		"data/projectile.png"		           // 0
	};

	// Prepare cursor icon textures
	const char* cursorTextures[] = {
		"data/cursor-icon.png"		           // 0
	};

	// Prepare coin textures
	const char* coinTextures[] = {
	"data/bronze_coin.png"		           // 0
	};

// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
// > > > > > > >    SPRITE POINTERS    < < < < < < < //
// | | | | | | | \ . . . . . . . . . / | | | | | | | //
Sprite* backgroundSpritePointer;
Sprite* background2SpritePointer;
Sprite* backgroundGameOverSpritePointer;
Sprite* doodleSpritePointer;
Sprite* gameSpritePointer;
Sprite* greenPlatformSpritePointer;
Sprite* fakePlatformSpritePointer;
Sprite* fakePlatformBreaking1SpritePointer;
Sprite* fakePlatformBreaking2SpritePointer;
Sprite* fakePlatformBreaking3SpritePointer;
Sprite* fakePlatformBreaking4SpritePointer;
Sprite* springBootsSpritePointer;
Sprite* itemSpritePointer;
Sprite* numberSpritePointer;
Sprite* topBarSpritePointer;
Sprite* bottomBarSpritePointer;
Sprite* playButtonSpritePointer;
Sprite* headerSpritePointer;
Sprite* gameOverSpritePointer;
Sprite* scoreSpritePointer;
Sprite* monsterSpritePointer;
Sprite* monsterDeadSpritePointer;
Sprite* projectileSpritePointer;
Sprite* cursorSpritePointer;
Sprite* coinSpritePointer;
Sprite* monsterIconSpritePointer;
Sprite* platformIconSpritePointer;


// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
// > > > > > > >     TEXTURE PATHS     < < < < < < < //
// | | | | | | | \ . . . . . . . . . / | | | | | | | //
const char* pathBackground;
const char* pathBackground2;
const char* pathBackgroundGameOver;
const char* pathDoodle;
const char* pathGame;
const char* pathGreenPlatform;
const char* pathFakePlatform;
const char* pathFakePlatformBreaking1;
const char* pathFakePlatformBreaking2;
const char* pathFakePlatformBreaking3;
const char* pathFakePlatformBreaking4;
const char* pathSpringBoots;
const char* pathItem;
const char* pathDigit;
const char* pathTopBar;
const char* pathBottomBar;
const char* pathPlayButton;
const char* pathHeader;
const char* pathGameOver;
const char* pathScore;
const char* pathMonster;
const char* pathMonsterDead;
const char* pathProjectile;
const char* pathCursor;
const char* pathCoin;


// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
// > > > > > > >       STRUCTURES      < < < < < < < //
// | | | | | | | \ . . . . . . . . . / | | | | | | | //

// Initial platform
struct PlatformPoint {

	int x = 0, y = 0, animation_time = 100;
	bool start_time = false;
	Sprite* sprite;
};

// Initial score
struct Number {

	int x = 0, y = 0, value = 0;
	const char* pathNumber[7] = { 0,0,0,0,0,0,0 };

	void updateNumber() 
	{
		int digit, rest = value, add_x = 0;

		for (int i = 6; i >= 0; i--)
		{
			if (rest > 0) 
			{
				digit = rest % 10;
				rest = rest / 10;
				pathNumber[i] = digitTextures[digit];
			}
			else pathNumber[i] = NULL;
		}

		for (int i = 0; i <= 6; i++)
		{
			if (pathNumber[i] != NULL)
			{
				if (pathNumber[i] == digitTextures[0]) add_x += (digit_width - 1);
				else if (pathNumber[i] == digitTextures[1]) add_x += (digit_width - 16);
				else if (pathNumber[i] == digitTextures[3]) add_x += (digit_width - 1);
				else if (pathNumber[i] == digitTextures[4]) add_x += (digit_width - 6);
				else if (pathNumber[i] == digitTextures[8]) add_x += (digit_width - 2);
				else if (pathNumber[i] == digitTextures[9]) add_x += (digit_width - 4);
				else add_x += digit_width;
				numberSpritePointer = createSprite(pathNumber[i]);
				drawSprite(numberSpritePointer, x + add_x - digit_width, y);
				destroySprite(numberSpritePointer);
			}
			else if (value == 0)
			{
				numberSpritePointer = createSprite(digitTextures[0]);
				drawSprite(numberSpritePointer, x, y);
				destroySprite(numberSpritePointer);
			}
		}
	}
};

// Initial structures
PlatformPoint platform[100];
Number score;
Number your_score;
Number high_score;
Number platforms_passed;
Number coins;
Number defeated_monsters;
Number special_power;

// Initial coin
struct Coin {

	int x = 0, y = 0;
	bool is_spawned = false;
	Sprite* sprite;

	void updateCoin()
	{
		drawSprite(sprite, x, y);

		// ======> Doodle touch a coin <======
		if ((doodle_position_x > x - 2 * doodle_width / 3) && (doodle_position_x < x + coin_width - doodle_width / 3) && (doodle_position_y < y + coin_height * 2 / 3) && (doodle_position_y + doodle_height > y))
		{
			is_spawned = false;
			coins.value++;
		}
	}
};
Coin coin[10];

// Initial monster
struct Monster {

	int x = 0, y = 0, animation_time = 100;
	bool start_time = false, is_spawned = false;
	Sprite* sprite;

	void updateDeathAnimation()
	{
		if (start_time == true && animation_time >= -50)
		{
			sprite = monsterDeadSpritePointer;
			y = y + (0.2 * (86 - animation_time));
			animation_time -= 1;    // <-- This number is responsible for the animation speed and must be a divisor of 60!
		}

		drawSprite(sprite, x, y);

		// ======> Doodle touch a monster <======
		if ((doodle_position_x > x - 2 * doodle_width / 3) && (doodle_position_x < x + monster_width - doodle_width / 3) && (doodle_position_y < y + monster_height * 2 / 3) && (doodle_position_y + doodle_height > y) && start_time == false)
		{
			// If the doodle jumped on the monster head - (monster die)
			if (falling_speed > 0)
			{
				start_time = true;
				defeated_monsters.value++;

				// doodle jump
				if (doodle_has_spring_boots == true) falling_speed = -22;
				else falling_speed = -14;
			}
			//If the doodle flew into the monster - (doodle die)
			else gameOver = true;
		}

	}
};
Monster monster[10];

// Initial projectile
struct Projectile {

	int x = 0, y = 0;
	bool is_spawned = false, direction_left = false;

	void updateMovement()
	{
		// Moves the projectile to the left or right depending on the direction
		if (direction_left) x -= projectail_speed;
		else x += projectail_speed;

		for (int i = 0; i < numberOfMonsters; i++)
		{
			// ======> Projectile touch a monster <======
			if (y > monster[i].y - projectile_length && y < monster[i].y + projectile_length + monster_height && x > monster[i].x + projectile_length && x < monster[i].x - projectile_length + monster_width)
			{
				// If the monster is alive, count it to defeated monsters
				if (monster[i].start_time == false) defeated_monsters.value++;

				// Starts posthumous animation
				monster[i].start_time = true;

				// Destroy a projectile on touch with a monster 
				is_spawned = false;                                               
			}
			drawSprite(projectileSpritePointer, x, y);
		}
	}
};
Projectile projectile[100];


// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
// > > > > > > >       FUNCTIONS       < < < < < < < //
// | | | | | | | \ . . . . . . . . . / | | | | | | | //

// Checking if this platform space is inappropriate - (function for while loop)
bool isABadPlaceForPlatformOrCoin() 
{
	// Checking potential collisions with all platforms
	for (int j = 0; j < numberOfPlatforms; j++)
	{
		if ((px - 1.5 * platform_width) < platform[j].x && (px + 1.5 * platform_width) > platform[j].x && (py - 3 * platform_height) < platform[j].y && (py + 3 * platform_height) > platform[j].y)
		{
			return true;	
		}
	}

	// Checking potential collisions with all coins
	for (int j = 0; j < numberOfCoins; j++)
	{
		if ((px - 1.5 * coin_width) < coin[j].x && (px + 1.5 * coin_width) > coin[j].x && (py - 3 * coin_height) < coin[j].y && (py + 3 * coin_height) > coin[j].y)
		{
			return true;
		}
	}

	return false;
}

// Function for start and restart the game
void startTheGame()
{
	// Residue cleaning and preparing variables
	doodle_position_x = (screen_width - doodle_width) / 2;
	doodle_position_y = (screen_height - doodle_height) / 2;
	falling_speed = -5;
	gameOver = false;
	gameStarted = false;
	title_screen = false;
	for (int i = 0; i < numberOfMonsters; i++) monster[i].is_spawned = false;
	for (int i = 0; i < numberOfProjectiles; i++) projectile[i].is_spawned = false;
	for (int i = 0; i < numberOfCoins; i++) coin[i].is_spawned = false;
	item_spawned = false;
	
	// Initialize the pseudo-random number generator
	std::srand(std::time(nullptr));

	// Initial co-ordinates for platforms
	for (int i = 0; i < numberOfPlatforms; i++)
	{
		do {
			px = std::rand() % (int)(screen_width - platform_width);
			py = std::rand() % (int)(screen_height - platform_height);
		} while (isABadPlaceForPlatformOrCoin());

		// Setting coordinates and variables
		platform[i].x = px;
		platform[i].y = py;
		platform[i].start_time = false;
		platform[i].animation_time = 100;

		// Fake platform draw - Probability 10%
		if (rand() % 10 == 1) platform[i].sprite = fakePlatformSpritePointer;
		// Green platform draw - Probability 90%
		else platform[i].sprite = greenPlatformSpritePointer;
	}

	// Initial co-ordinates for coins
	for (int i = 0; i < numberOfCoins; i++)
	{
		// Coin draw - Probability 50%
		if (rand() % 2 == 1)
		{
			// Generation of new appropriate coin coordinates
			do {
				px = std::rand() % (int)(screen_width - coin_width);
				py = std::rand() % (int)(screen_height - coin_height);
			} while (isABadPlaceForPlatformOrCoin());

			// Setting coordinates and variables
			coin[i].x = px;
			coin[i].y = py;
			coin[i].sprite = coinSpritePointer;
			coin[i].is_spawned = true;
		}
	}
}


// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
// > > > > > > >       FRAMEWORK       < < < < < < < //
// | | | | | | | \ . . . . . . . . . / | | | | | | | //
class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		bool is_valid_width = false;
		bool is_valid_height = false;
		bool is_valid_fullscreen = false;

		std::cout << "======= Game resolution settings =======\n" << std::endl;

		while (!is_valid_width)
		{
			std::cout << "Enter the width: ";
			if (std::cin >> width && width >= 500 && width <= 1920)
			{
				is_valid_width = true;
			}
			else
			{
				std::cout << "Invalid number, please try again. Width in <500,1920>." << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}

		while (!is_valid_height)
		{
			std::cout << "Enter the height: ";
			if (std::cin >> height && height >= 500 && height <= 1080)
			{
				is_valid_height = true;
			}
			else
			{
				std::cout << "Invalid number, please try again. Height in <500,1080>." << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}

		while (!is_valid_fullscreen)
		{
			std::cout << "Do you want fullscreen? [0|1]: ";
			if (std::cin >> fullscreen)
			{
				is_valid_fullscreen = true;
			}
			else
			{
				std::cout << "Invalid bool value, please enter [ 0 = false / 1 = true ]" << std::endl;
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}

		std::cout << "\n========================================\n" << std::endl;
		std::cout << "Resolution: " << width << "x" << height << std::endl;
		if (fullscreen == 1) std::cout << "Fullscreen: true" << std::endl;
		else std::cout << "Fullscreen: false" << std::endl << std::endl;

	}

	virtual bool Init() {

		// Hide cursor
		showCursor(false);

		// Get screen size
		getScreenSize(w, h);

		// Prepare initial textures
		pathBackground = backgroundTextures[0];
		pathBackground2 = backgroundTextures[1];
		pathBackgroundGameOver = backgroundTextures[2];
		pathDoodle = doodleClassicTextures[0];
		pathGame = gameTextures[0];
		pathGreenPlatform = platformTextures[0];
		pathFakePlatform = platformTextures[1];
		pathFakePlatformBreaking1 = platformTextures[2];
		pathFakePlatformBreaking2 = platformTextures[3];
		pathFakePlatformBreaking3 = platformTextures[4];
		pathFakePlatformBreaking4 = platformTextures[5];
		pathSpringBoots = springBootsTextures[1];
		pathItem = itemTextures[0];
		pathTopBar = barTextures[0];
		pathBottomBar = barTextures[1];
		pathDigit = digitTextures[0];
		pathPlayButton = playButtonTextures[0];
		pathHeader = headerTextures[0];
		pathGameOver = headerTextures[1];
		pathScore = textTextures[2];
		pathMonster = monsterTextures[0];
		pathMonsterDead = monsterTextures[1];
		pathProjectile = projectileTextures[0];
		pathCursor = cursorTextures[0];
		pathCoin = coinTextures[0];

		// Load initial textures
		backgroundSpritePointer = createSprite(pathBackground);
		background2SpritePointer = createSprite(pathBackground2);
		backgroundGameOverSpritePointer = createSprite(pathBackgroundGameOver);
		doodleSpritePointer = createSprite(pathDoodle);
		greenPlatformSpritePointer = createSprite(pathGreenPlatform);
		fakePlatformSpritePointer = createSprite(pathFakePlatform);
		fakePlatformBreaking1SpritePointer = createSprite(pathFakePlatformBreaking1);
		fakePlatformBreaking2SpritePointer = createSprite(pathFakePlatformBreaking2);
		fakePlatformBreaking3SpritePointer = createSprite(pathFakePlatformBreaking3);
		fakePlatformBreaking4SpritePointer = createSprite(pathFakePlatformBreaking4);
		springBootsSpritePointer = createSprite(pathSpringBoots);
		itemSpritePointer = createSprite(pathItem);
		topBarSpritePointer = createSprite(pathTopBar);
		bottomBarSpritePointer = createSprite(pathBottomBar);
		numberSpritePointer = createSprite(pathDigit);
		playButtonSpritePointer = createSprite(pathPlayButton);
		headerSpritePointer = createSprite(pathHeader);
		gameOverSpritePointer = createSprite(pathGameOver);
		scoreSpritePointer = createSprite(pathScore);
		monsterSpritePointer = createSprite(pathMonster);
		monsterDeadSpritePointer = createSprite(pathMonsterDead);
		projectileSpritePointer = createSprite(pathProjectile);
		cursorSpritePointer = createSprite(pathCursor);
		coinSpritePointer = createSprite(pathCoin);
		monsterIconSpritePointer = createSprite(pathMonster);
		platformIconSpritePointer = createSprite(pathGreenPlatform);

		// Set size of initial textures
		setSpriteSize(backgroundSpritePointer, screen_width / 2, screen_height);
		setSpriteSize(background2SpritePointer, screen_width / 2, screen_height);
		setSpriteSize(backgroundGameOverSpritePointer, screen_width, screen_height);
		setSpriteSize(doodleSpritePointer, doodle_width, doodle_height);
		setSpriteSize(greenPlatformSpritePointer, platform_width, platform_height);
		setSpriteSize(fakePlatformSpritePointer, platform_width, platform_height);
		setSpriteSize(fakePlatformBreaking1SpritePointer, platform_width, platform_height * 2.5);
		setSpriteSize(fakePlatformBreaking2SpritePointer, platform_width, platform_height * 2.5);
		setSpriteSize(fakePlatformBreaking3SpritePointer, platform_width, platform_height * 2.5);
		setSpriteSize(fakePlatformBreaking4SpritePointer, platform_width, platform_height * 2.5);
		setSpriteSize(springBootsSpritePointer, doodle_width, doodle_height);
		setSpriteSize(itemSpritePointer, item_width, item_height);
		setSpriteSize(topBarSpritePointer, screen_width, digit_height * 2);
		setSpriteSize(bottomBarSpritePointer, screen_width, digit_height * 2);
		setSpriteSize(numberSpritePointer, digit_width, digit_height);
		setSpriteSize(playButtonSpritePointer, play_button_width, play_button_height);
		setSpriteSize(headerSpritePointer, play_button_width * 2, play_button_height * 2);
		setSpriteSize(gameOverSpritePointer, play_button_width * 2, play_button_height * 2);
		setSpriteSize(scoreSpritePointer, play_button_width, play_button_height + digit_height);
		setSpriteSize(monsterSpritePointer, monster_width, monster_height);
		setSpriteSize(monsterDeadSpritePointer, monster_width, monster_height);
		setSpriteSize(projectileSpritePointer, projectile_length, projectile_length);
		setSpriteSize(cursorSpritePointer, cursor_width, cursor_height);
		setSpriteSize(coinSpritePointer, coin_width, coin_height);
		setSpriteSize(monsterIconSpritePointer, monster_width * 2 / 3, monster_height * 2 / 3);
		setSpriteSize(platformIconSpritePointer, platform_width / 2, platform_height / 2);

		// Load file and read the high score
		std::ifstream saved_high_score("saved_high_score.txt");
		saved_high_score >> high_score.value;
		saved_high_score.close();

		// Preparation of variables
		numberOfPlatforms = screen_width * screen_height / 25000;
		numberOfMonsters = screen_width * screen_height / 200000;
		numberOfCoins = screen_width* screen_height / 100000;
		doodle_jump_h = screen_height / 3;
		doodle_position_x = (screen_width / 2) - (doodle_width / 2);
		doodle_position_y = screen_height - (2 * doodle_height);
		game_over_screen_y = screen_height;
		cursor_position_x = screen_width;
		cursor_position_y = screen_height;

		// Initial co-ordinates for scores
		score.x = digit_width / 2;
		score.y = digit_height / 4;
		coins.x = screen_width / 4 + 3 * digit_width;
		coins.y = digit_height / 4;
		platforms_passed.x = screen_width / 2 + digit_width * 2;
		platforms_passed.y = digit_height / 4;
		defeated_monsters.x = screen_width * 3 / 4 + digit_width * 2;
		defeated_monsters.y = digit_height / 4;

		return true;
	}

	virtual void Close() {
		
		// In case of unexpected closing of the application, it will save your record to a file
		if (score.value > high_score.value)
		{
			std::ofstream saved_high_score("saved_high_score.txt");
			saved_high_score << score.value;
			saved_high_score.close();
		}
	}

	virtual bool Tick() {

		// -----------------------------------------------------------------
		//					This is support for FPS system			
							 frameStart = getTickCount(); 
		// -----------------------------------------------------------------


		// > > > > > > > > > > > > > > > > < < < < < < < < < < < < < < < < <
		// > > > > > Initialize the pseudo-random number generator < < < < <
		// > > > > > > > > > > > > > > > > < < < < < < < < < < < < < < < < <
		std::srand(std::time(nullptr));
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist_x(0, screen_width - platform_width);
		std::uniform_int_distribution<int> dist_y(0, 6 * platform_height);
		std::uniform_int_distribution<int> dist_item(0, platform_width - item_width);


		// =================================================================
		// >>>>>>>>>>>>>>>>>>>>>>>>  TITLE SCREEN  <<<<<<<<<<<<<<<<<<<<<<<<<
		// =================================================================
		if (title_screen == true)
		{
			// Changing button appearances and adding functionality
			if (mouse_on_play_button)
			{
				pathPlayButton = playButtonTextures[1];
				if (mouse_left_click) startTheGame();
			}
			else pathPlayButton = playButtonTextures[0];

			// Game over screen speed animation
			if (game_over_screen_y > 0) game_over_screen_y /= game_over_screen_y;
			else game_over_screen_y = 0;
		}

		
		// =================================================================
		// >>>>>>>>>>>  GAME OVER CONDITIONS  + game over screen <<<<<<<<<<<
		// =================================================================
		else
		if (doodle_position_y > screen_height || gameOver == true)
		{
			// Preparing to show game over screen
			spring_boots_time = false;
			doodle_has_spring_boots = false;
			game_title_screen_animation = false;
			gameOver = true;

			// Platforms animation after losing
			for (int i = 0; i < numberOfPlatforms; i++)
			{
				if (gameOver == false) platform[i].animation_time = 100;
				//platform[i].start_time = true;
				
				if (platform[i].animation_time >= 0)
				{
					platform[i].y = platform[i].y - (0.2 * platform[i].animation_time);
					platform[i].animation_time -= 1;    // <-- This number is responsible for the animation speed and must be a divisor of 60!
				}
				drawSprite(platform[i].sprite, platform[i].x, platform[i].y);
			}

			// Game over screen speed animation
			if (game_over_screen_y > 0) game_over_screen_y /= 2;
			else game_over_screen_y = 0;

			// Changing button appearances and adding functionality
			if (mouse_on_play_button)
			{
				pathPlayButton = playButtonTextures[4];
				if (mouse_left_click) startTheGame();
			}
			else
			{
				pathPlayButton = playButtonTextures[3];
			}

			// Load file and save the high score
			if (score.value > high_score.value)
			{
				high_score.value = score.value;
				std::ofstream saved_high_score("saved_high_score.txt");
				saved_high_score << score.value;
				saved_high_score.close();
			}

			// Preparing places for scores
			your_score.value = score.value;
			your_score.x = screen_width / 2 + digit_width;
			your_score.y = screen_height * 2 / 5 + game_over_screen_y;
			high_score.x = screen_width / 2 + digit_width / 2;
			high_score.y = screen_height * 2 / 5 + digit_height * 2 + game_over_screen_y;
			
		}

		// =================================================================
		// >>>>>>>>>>>>>>>>  ONGOING GAME  + playing screen <<<<<<<<<<<<<<<<   
		// =================================================================
		else
		{
			// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			// >>>>>>>>>>>>>>>>>>>>>>>>>>  Before the game starts  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			if (gameStarted == false)
			{
				// Reset the current score
				score.value = 0;
				coins.value = 0;
				platforms_passed.value = 0;
				defeated_monsters.value = 0;
				special_power.value = 0;

				// Preparing to show ongoing game screen
				gameOver = false;
				title_screen = false;

				// One extra rule before starting the game so you won't lose it early
				if (doodle_position_y > (screen_height - doodle_height))
				{
					falling_speed = -14;
				}
			}


			// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			// >>>>>>>>>>>>>>>>>>>>>>>>>>>  The game has started  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			else
			{
				// ========================= PICKING UP THE SPRING BOOTS =========================
				if ((doodle_position_x > item_position_x - 2 * doodle_width / 3) && (doodle_position_x < item_position_x + item_width - doodle_width / 3) && (doodle_position_y + doodle_height < item_position_y + item_height) && (doodle_position_y + doodle_height > item_position_y - 2))
				{
					item_spawned = false;
					doodle_has_spring_boots = true;
					spring_boots_time = 1200;   // <-- 20 seconds
				}

				// ======================== BOUNCING UP ON THE PLATFORMS ========================
				for (int i = 0; i < numberOfPlatforms; i++)
				{
					if ((doodle_position_x > platform[i].x - 2 * doodle_width / 3) && (doodle_position_x < platform[i].x + platform_width - doodle_width / 3) && (doodle_position_y + doodle_height < platform[i].y + 2 * platform_height / 3) && (doodle_position_y + doodle_height > platform[i].y - 2) && (falling_speed > 0))
					{
						// If it's a good platform, you jump
						if (platform[i].sprite == greenPlatformSpritePointer)
						{
							if (doodle_has_spring_boots == true)
							{
								falling_speed = -22;
							}
							else
							{
								falling_speed = -14;
							}
						}
						// If it's a fake platform, you fall
						else
						{
							platform[i].start_time = true;
						}
					}
				}
				
				// ========================== FAKE PLATFORMS ANIMATION ===========================
				for (int i = 0; i < numberOfPlatforms; i++)
				{
					if (platform[i].start_time == true && platform[i].animation_time >= -50)
					{
						if (platform[i].animation_time > 98) platform[i].sprite = fakePlatformBreaking1SpritePointer;
						else if (platform[i].animation_time > 96) platform[i].sprite = fakePlatformBreaking2SpritePointer;
						else if (platform[i].animation_time > 94) platform[i].sprite = fakePlatformBreaking3SpritePointer;
						else
						{
							platform[i].sprite = fakePlatformBreaking3SpritePointer;
							platform[i].y = platform[i].y + (0.2 * (86 - platform[i].animation_time));
						}
						platform[i].animation_time -= 1;  // <-- This number is responsible for the animation speed and must be a divisor of 60!
					}
					drawSprite(platform[i].sprite, platform[i].x, platform[i].y);
				}
				
				// =============================== THINGS TO COUNT ===============================

				// Countdown time of using spring boots - (20 seconds)
				if (spring_boots_time > 0)
				{
					spring_boots_time--;
					special_power.value = spring_boots_time / 60 + 1;
					if (special_power.value > 9) special_power.x = doodle_position_x + doodle_width / 3 - 6;
					else special_power.x = doodle_position_x + doodle_width / 3;
					special_power.y = doodle_position_y - 8;
				}
				else
				{
					spring_boots_time = 0;
					doodle_has_spring_boots = false;
				}

				// Countinmg the distance traveled by the doodle (counting pixels on the screen) - first part of code
				if (doodle_position_y > doodle_jump_h)
				{
					counting_score = screen_height - doodle_position_y + doodle_height;
					if (counting_score > score.value) score.value = counting_score;
				}

				// ========================= MOVING THE SCREEN SYSTEM ============================
				if (doodle_position_y < doodle_jump_h)
				{
					// Counting the distance traveled by the doodle (counting pixels on the screen) - second part of code
					score.value += (doodle_jump_h - doodle_position_y);
					doodle_position_y = doodle_jump_h;

					// ----------------------------------> FALLING SYSTEM <----------------------------------
					// >>> Moving down items
					item_position_y = item_position_y - falling_speed;
					if (item_position_y > screen_height) item_spawned = false;

					// >>> Moving down monsters
					for (int i = 0; i < numberOfMonsters; i++)
					{
						if (monster[i].is_spawned == true)
						{
							monster[i].y = monster[i].y - falling_speed;
							if (monster[i].y > screen_height) monster[i].is_spawned = false;
						}
					}

					// >>> Moving down projectiles
					for (int i = 0; i < numberOfProjectiles; i++)
					{
						if (projectile[i].is_spawned == true)
						{
							projectile[i].y = projectile[i].y - falling_speed;
							if (projectile[i].y > screen_height) projectile[i].is_spawned = false;
						}
					}

					// >>> Moving down platforms
					for (int i = 0; i < numberOfPlatforms; i++)
					{
						platform[i].y = platform[i].y - falling_speed;

						// -------------->> Creating new platforms <<--------------
						if (platform[i].y > screen_height)
						{
							platforms_passed.value += 1;

							// Generation of new appropriate platform coordinates
							do {
								px = dist_x(mt);
								py = -(dist_y(mt));
							} while (isABadPlaceForPlatformOrCoin());

							// Setting coordinates and variables
							platform[i].x = px;
							platform[i].y = py;
							platform[i].start_time = false;
							platform[i].animation_time = 100;

							// Fake platform draw - Probability 10%
							if (dist_x(mt) % 10 == 1) platform[i].sprite = fakePlatformSpritePointer;
							// Green platform draw - Probability 90%
							else
							{
								platform[i].sprite = greenPlatformSpritePointer;

								// Item on platform draw - (spring boots) - Probability ~7%
								if (dist_x(mt) % 15 == 2 && doodle_has_spring_boots == false && item_spawned == false)
								{
									item_position_x = platform[i].x + dist_item(mt);
									item_position_y = platform[i].y - item_height;
									item_spawned = true;
								}
								// Monster on platform draw - Probability 10%
								else if (dist_x(mt) % 10 == 3)
								{
									for (int j = 0; j < numberOfMonsters; j++) 
									{
										if (monster[j].is_spawned == false)
										{
											monster[j].x = platform[i].x;
											monster[j].y = platform[i].y - monster_height;
											monster[j].animation_time = 100;
											monster[j].start_time = false;
											monster[j].is_spawned = true;
											monster[j].sprite = monsterSpritePointer;
											break;
										}
									}
								}
							}
						}
					}

					// >>> Moving down coins
					for (int i = 0; i < numberOfCoins; i++)
					{
						coin[i].y = coin[i].y - falling_speed;

						// -------------->> Creating new coins <<--------------
						if (coin[i].y > screen_height)
						{
							// Coin draw - Probability 1% (in every frame)
							if (dist_x(mt) % 100 == 4)
							{
								// Generation of new appropriate coin coordinates
								do {
									px = dist_x(mt);
									py = -(dist_y(mt));
								} while (isABadPlaceForPlatformOrCoin());

								// Setting coordinates and variables
								coin[i].x = px;
								coin[i].y = py;
								coin[i].sprite = coinSpritePointer;
								coin[i].is_spawned = true;
							}
						}
					}
					// --------------------------------------------------------------------------------------
				}
				
				// =============================== DOODLE MOVEMENT =================================
				if (doodle_position_x > (screen_width - doodle_width) / 2)
				{
					if (doodle_left_movement == true) doodle_position_x -= 6;
					if (doodle_right_movement == true) doodle_position_x += 6;
				}
				else
				{
					if (doodle_left_movement == true) doodle_position_x -= 4;
					if (doodle_right_movement == true) doodle_position_x += 4;
				}
			} //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


			// ==================== DOODLE AND PROJECTILES ON THE OTHER SIDE =======================
			if (doodle_position_x > screen_width) doodle_position_x -= screen_width;
			if (doodle_position_x < 0) doodle_position_x += screen_width;
			for (int i = 0; i < numberOfProjectiles; i++)
			{
				if (projectile[i].x > screen_width) projectile[i].x -= screen_width;
				if (projectile[i].x < 0) projectile[i].x += screen_width;
			}

			// ======================== GAME OVER SCREEN - SPEED ANIMATION =========================
			if (game_over_screen_y < screen_height)
			{
				if (game_over_screen_y == 0) game_over_screen_y = 1;
				game_over_screen_y = game_over_screen_y * 2;
			}
			else game_over_screen_y = screen_height;

		}
		// =========================================================================================


		// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
		// > > > > > > >    Falling  system    < < < < < < < //
		// | | | | | | | \ . . . . . . . . . / | | | | | | | //
		falling_speed += 0.4;
		doodle_position_y += falling_speed;
		

		// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
		// > > > > > > >   Prepare  textures   < < < < < < < //
		// | | | | | | | \ . . . . . . . . . / | | | | | | | //
		if (doodle_has_spring_boots == true)  // ------->  Set textures for doodle with the spring boots  <-------
		{
			if (which_key_is_pressed == FRKey::LEFT)
			{
				pathDoodle = doodleClassicTextures[1];                                                    // doodle has shorter legs
				if (falling_speed < -19 || falling_speed > 10) pathSpringBoots = springBootsTextures[2];  // spring boots when doodle stays on platform
				else if (falling_speed < -12) pathSpringBoots = springBootsTextures[0];                   // spring boots when doodle is jumping
				else pathSpringBoots = springBootsTextures[1];                                            // spring boots normal look
			}
			if (which_key_is_pressed == FRKey::RIGHT)
			{
				pathDoodle = doodleClassicTextures[5];                                                    // doodle has shorter legs
				if (falling_speed < -19 || falling_speed > 10) pathSpringBoots = springBootsTextures[5];  // spring boots when doodle stays on platform
				else if (falling_speed < -12) pathSpringBoots = springBootsTextures[3];                   // spring boots when doodle is jumping
				else pathSpringBoots = springBootsTextures[4];                                            // spring boots normal look
			}
		}
		else								  // ---------------->  Set textures for doodle only <----------------
		{
			if (falling_speed < 0)																		  // > when doodle goes up <
			{
				if (which_key_is_pressed == FRKey::LEFT) pathDoodle = doodleClassicTextures[0];
				if (which_key_is_pressed == FRKey::RIGHT) pathDoodle = doodleClassicTextures[4];
			}
			else																						  // > when doodle falls down <
			{
				if (which_key_is_pressed == FRKey::LEFT) pathDoodle = doodleClassicTextures[1];
				if (which_key_is_pressed == FRKey::RIGHT) pathDoodle = doodleClassicTextures[5];
			}
		}


		// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
		// > > > > > > >     Load textures     < < < < < < < //
		// | | | | | | | \ . . . . . . . . . / | | | | | | | //
		doodleSpritePointer = createSprite(pathDoodle);
		springBootsSpritePointer = createSprite(pathSpringBoots);
		playButtonSpritePointer = createSprite(pathPlayButton);
		setSpriteSize(doodleSpritePointer, doodle_width, doodle_height);
		setSpriteSize(springBootsSpritePointer, doodle_width, doodle_height);


		// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
		// > > > > > > >     Draw textures     < < < < < < < //
		// | | | | | | | \ . . . . . . . . . / | | | | | | | //
		if (title_screen)
		{
			drawSprite(backgroundGameOverSpritePointer, 0, 0);
			drawSprite(headerSpritePointer, (screen_width - play_button_width * 2) / 2, screen_height / 5);
			drawSprite(playButtonSpritePointer, (screen_width - play_button_width) / 2, screen_height * 3 / 5 + digit_height);
			drawSprite(bottomBarSpritePointer, 0, screen_height - (digit_height * 2));
			drawSprite(topBarSpritePointer, 0, 0);
			drawSprite(cursorSpritePointer, cursor_position_x, cursor_position_y);
		}
		else if (gameOver)
		{
			drawSprite(backgroundGameOverSpritePointer, 0, game_over_screen_y);
			drawSprite(gameOverSpritePointer, (screen_width - play_button_width * 2) / 2, screen_height / 5 - digit_height + game_over_screen_y);
			drawSprite(playButtonSpritePointer, (screen_width - play_button_width) / 2, screen_height * 3 / 5 + digit_height + game_over_screen_y);
			drawSprite(scoreSpritePointer, screen_width / 2 - play_button_width, screen_height * 2 / 5 + game_over_screen_y);
			drawSprite(bottomBarSpritePointer, 0, screen_height - (digit_height * 2) + game_over_screen_y);
			drawSprite(topBarSpritePointer, 0, 0);
			score.updateNumber();
			coins.updateNumber();
			your_score.updateNumber();
			high_score.updateNumber();
			platforms_passed.updateNumber();
			defeated_monsters.updateNumber();
			drawSprite(coinSpritePointer, coins.x - coin_width - digit_width / 2, coins.y);
			drawSprite(platformIconSpritePointer, platforms_passed.x - (platform_width * 2 / 3) + digit_width / 2, platforms_passed.y + 10);
			drawSprite(monsterIconSpritePointer, defeated_monsters.x - monster_width / 2 - digit_width / 2, defeated_monsters.y + 4);
			drawSprite(cursorSpritePointer, cursor_position_x, cursor_position_y);
		}
		else //(Ongoing game)
		{
			drawSprite(backgroundSpritePointer, 0, 0);
			drawSprite(background2SpritePointer, screen_width / 2, 0);
			for (int i = 0; i < numberOfPlatforms; i++) drawSprite(platform[i].sprite, platform[i].x, platform[i].y);
			for (int i = 0; i < numberOfProjectiles; i++) if (projectile[i].is_spawned == true) projectile[i].updateMovement();
			for (int i = 0; i < numberOfMonsters; i++) if (monster[i].is_spawned == true) monster[i].updateDeathAnimation();
			for (int i = 0; i < numberOfCoins; i++) if (coin[i].is_spawned == true) coin[i].updateCoin();
			if (item_position_x > 0 && doodle_has_spring_boots == false && item_spawned == true) drawSprite(itemSpritePointer, item_position_x, item_position_y);
			drawSprite(doodleSpritePointer, doodle_position_x, doodle_position_y);
			drawSprite(doodleSpritePointer, doodle_position_x - screen_width, doodle_position_y);
			drawSprite(doodleSpritePointer, doodle_position_x + screen_width, doodle_position_y);
			if (doodle_has_spring_boots) drawSprite(springBootsSpritePointer, doodle_position_x, doodle_position_y + doodle_height / 3);

			// Screen transition animation
			if (game_over_screen_y < screen_height)
			{
				if (game_title_screen_animation)
				{
					drawSprite(backgroundGameOverSpritePointer, 0, game_over_screen_y);
					drawSprite(headerSpritePointer, (screen_width - play_button_width * 2) / 2, screen_height / 5 + game_over_screen_y);
					drawSprite(playButtonSpritePointer, (screen_width - play_button_width) / 2, screen_height * 3 / 5 + digit_height + game_over_screen_y);
					drawSprite(bottomBarSpritePointer, 0, screen_height - (digit_height * 2) + game_over_screen_y);
				}
				else
				{
					drawSprite(backgroundGameOverSpritePointer, 0, game_over_screen_y);
					drawSprite(gameOverSpritePointer, (screen_width - play_button_width * 2) / 2, screen_height / 5 - digit_height + game_over_screen_y);
					drawSprite(playButtonSpritePointer, (screen_width - play_button_width) / 2, screen_height * 3 / 5 + digit_height + game_over_screen_y);
					drawSprite(scoreSpritePointer, screen_width / 2 - play_button_width, screen_height * 2 / 5 + game_over_screen_y);
					drawSprite(bottomBarSpritePointer, 0, screen_height - (digit_height * 2) + game_over_screen_y);
				}
			}

			// Update score number and show it with top bar
			drawSprite(topBarSpritePointer, 0, 0);
			drawSprite(coinSpritePointer, coins.x - coin_width - digit_width/2, coins.y);
			drawSprite(platformIconSpritePointer, platforms_passed.x - (platform_width * 2 / 3) + digit_width / 2, platforms_passed.y + 10);
			drawSprite(monsterIconSpritePointer, defeated_monsters.x - monster_width / 2 - digit_width / 2, defeated_monsters.y + 4);
			score.updateNumber();
			coins.updateNumber();
			platforms_passed.updateNumber();
			defeated_monsters.updateNumber();
			if (spring_boots_time > 0) special_power.updateNumber();
		}


		// | | | | | | | / ' ' ' ' ' ' ' ' ' \ | | | | | | | //
		// > > > > > > >   Destroy  textures   < < < < < < < //
		// | | | | | | | \ . . . . . . . . . / | | | | | | | //
		destroySprite(doodleSpritePointer);
		destroySprite(springBootsSpritePointer);
		destroySprite(playButtonSpritePointer);
		

		// -----------------------------------------------------------------
		//                 FPS - Limiting Frame Rate System
		frameTime = getTickCount() - frameStart;
		if (frameDelay > frameTime)
		{
			std::chrono::milliseconds miliseconds(frameDelay - frameTime);
			std::this_thread::sleep_for(miliseconds);
		}
		// -----------------------------------------------------------------

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

		// "If" - For optimization
		if (title_screen || gameOver)
		{
			// Update cursor position
			cursor_position_x = x;
			cursor_position_y = y;

			// Cursor on play button
			if (x > (screen_width - play_button_width) / 2 && x < (screen_width + play_button_width) / 2 && y >(screen_height * 3 / 5 + digit_height) && y < (screen_height * 3 / 5 + digit_height + play_button_height))
			{
				std::cout << "Cursor on play button" << std::endl;
				mouse_on_play_button = true;

			}
			else
			{
				mouse_on_play_button = false;

			}
		}
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

		if (button == FRMouseButton::LEFT)
		{
			mouse_left_click = !isReleased;

			if (mouse_left_click)
			{
				std::cout << "Left mouse button clicked " << mouse_left_click << std::endl;

				// Shoot a projectile
				for (int i = 0; i < numberOfProjectiles; i++)
				{
					if (projectile[i].is_spawned == false)
					{
						if (which_key_is_pressed == FRKey::LEFT)
						{
							projectile[i].direction_left = true;
							projectile[i].x = doodle_position_x - projectile_length;
						}
						else
						{
							projectile[i].direction_left = false;
							projectile[i].x = doodle_position_x + doodle_width;
						}
						projectile[i].y = doodle_position_y + doodle_height / 2;
						projectile[i].is_spawned = true;
						break;
					}
				}
			}
			else
			{
				std::cout << "Left mouse button unclicked " << mouse_left_click << std::endl;

				
			}
		}

		if (button == FRMouseButton::RIGHT)
		{
			mouse_right_click = !isReleased;

			if (mouse_right_click)
			{
				std::cout << "Right mouse button clicked " << mouse_right_click << std::endl;

				// Use a special power - "spring boots" - (cost 20 coins)
				if (coins.value >= 20)
				{
					coins.value -= 20;
					item_spawned = false;
					doodle_has_spring_boots = true;
					spring_boots_time = 1200;   // <-- 20 seconds
				}
			}
			else
			{
				std::cout << "Right mouse button unclicked " << mouse_right_click << std::endl;
				
			}
		}
	}

	virtual void onKeyPressed(FRKey k) {


		if (k == FRKey::LEFT)
		{
			gameStarted = true;
			which_key_is_pressed = k;
			doodle_left_movement = true;
		}

		if (k == FRKey::RIGHT)
		{
			gameStarted = true;
			which_key_is_pressed = k;
			doodle_right_movement = true;
		}

	}

	virtual void onKeyReleased(FRKey k) {

		if (k == FRKey::LEFT)
		{
			doodle_left_movement = false;
			if (doodle_right_movement == true) which_key_is_pressed = FRKey::RIGHT;
		}

		if (k == FRKey::RIGHT)
		{
			doodle_right_movement = false;
			if (doodle_left_movement == true) which_key_is_pressed = FRKey::LEFT;
		}
		
	}

	virtual const char* GetTitle() override
	{
		return "Doodle Jump Game";
	}

};

int main(int argc, char* argv[])
{

	MyFramework MyGame;

	run(&MyGame);

	return 0;
}
