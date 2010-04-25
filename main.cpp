
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <unistd.h>

#include "utils.h"
#include "defs.h"

#include "audio.h"
#include "video.h"
#include "gui.h"
#include "input.h"
#include "script.h"
#include "system.h"

#include "global.h"

#include "mode_manager.h"
#include "map.h"
#include "main_options.h"



void QuitGame() {
	ModeEngine::SingletonDestroy();
	GameGlobal::SingletonDestroy();
	GUISystem::SingletonDestroy();
	AudioEngine::SingletonDestroy();
	InputEngine::SingletonDestroy();
	ScriptEngine::SingletonDestroy();
	SystemEngine::SingletonDestroy();
	VideoEngine::SingletonDestroy();
}

bool LoadSettings()
{
	ReadScriptDescriptor settings;
	if (settings.OpenFile(GetSettingsFilename()) == false)
		return false;

	settings.OpenTable("settings");
	settings.OpenTable("key_settings");
	InputManager->SetUpKey(static_cast<SDLKey>(settings.ReadInt("up")));
	InputManager->SetDownKey(static_cast<SDLKey>(settings.ReadInt("down")));
	InputManager->SetLeftKey(static_cast<SDLKey>(settings.ReadInt("left")));
	InputManager->SetRightKey(static_cast<SDLKey>(settings.ReadInt("right")));
	InputManager->SetConfirmKey(static_cast<SDLKey>(settings.ReadInt("confirm")));
	InputManager->SetCancelKey(static_cast<SDLKey>(settings.ReadInt("cancel")));
	InputManager->SetMenuKey(static_cast<SDLKey>(settings.ReadInt("menu")));
	InputManager->SetSwapKey(static_cast<SDLKey>(settings.ReadInt("swap")));
	InputManager->SetLeftSelectKey(static_cast<SDLKey>(settings.ReadInt("left_select")));
	InputManager->SetRightSelectKey(static_cast<SDLKey>(settings.ReadInt("right_select")));
	InputManager->SetPauseKey(static_cast<SDLKey>(settings.ReadInt("pause")));
	settings.CloseTable();
	if (settings.IsErrorDetected()) {
		cerr << "SETTINGS LOAD ERROR: failure while trying to retrieve key map "
			<< "information from file: " << GetSettingsFilename() << endl;
		cerr << settings.GetErrorMessages() << endl;
		return false;
	}
	settings.OpenTable("video_settings");
	bool fullscreen = settings.ReadBool("full_screen");
	int32 resx = settings.ReadInt("screen_resx");
	int32 resy = settings.ReadInt("screen_resy");
	VideoManager->SetInitialResolution(resx, resy);
	VideoManager->SetFullscreen(fullscreen);
	settings.CloseTable();
	if (settings.IsErrorDetected()) {
		cerr << "SETTINGS LOAD ERROR: failure while trying to retrieve video settings "
			<< "information from file: " << GetSettingsFilename() << endl;
		cerr << settings.GetErrorMessages() << endl;
		return false;
	}
	if (AUDIO_ENABLE) {
		settings.OpenTable("audio_settings");
		AudioManager->SetMusicVolume(static_cast<float>(settings.ReadFloat("music_vol")));
		AudioManager->SetSoundVolume(static_cast<float>(settings.ReadFloat("sound_vol")));
	}
	settings.CloseAllTables();
	if (settings.IsErrorDetected()) {
		cerr << "SETTINGS LOAD ERROR: failure while trying to retrieve audio settings "
			<< "information from file: " << GetSettingsFilename() << endl;
		cerr << settings.GetErrorMessages() << endl;
		return false;
	}
	settings.CloseFile();
	return true;
}


void InitializeEngine() throw (Exception) {
	// Create and initialize singleton class managers
	AudioManager = AudioEngine::SingletonCreate();
	InputManager = InputEngine::SingletonCreate();
	VideoManager = VideoEngine::SingletonCreate();
	ScriptManager = ScriptEngine::SingletonCreate();
	SystemManager = SystemEngine::SingletonCreate();
	ModeManager = ModeEngine::SingletonCreate();
	GUIManager = GUISystem::SingletonCreate();
	GlobalManager = GameGlobal::SingletonCreate();

	if (VideoManager->SingletonInitialize() == false)
		throw Exception("ERROR: unable to initialize VideoManager", __FILE__, __LINE__, __FUNCTION__);
	if (AudioManager->SingletonInitialize() == false)
		throw Exception("ERROR: unable to initialize AudioManager", __FILE__, __LINE__, __FUNCTION__);
	if (ScriptManager->SingletonInitialize() == false)
		throw Exception("ERROR: unable to initialize ScriptManager", __FILE__, __LINE__, __FUNCTION__);
	if (SystemManager->SingletonInitialize() == false)
		throw Exception("ERROR: unable to initialize SystemManager", __FILE__, __LINE__, __FUNCTION__);
	if (InputManager->SingletonInitialize() == false)
		throw Exception("ERROR: unable to initialize InputManager", __FILE__, __LINE__, __FUNCTION__);
	if (ModeManager->SingletonInitialize() == false)
		throw Exception("ERROR: unable to initialize ModeManager", __FILE__, __LINE__, __FUNCTION__);
	if (GlobalManager->SingletonInitialize() == false)
		throw Exception("ERROR: unable to initialize GlobalManager", __FILE__, __LINE__, __FUNCTION__);
	if (LoadSettings() == false)
		throw Exception("ERROR: Unable to load settings file", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->ApplySettings() == false)
		throw Exception("ERROR: Unable to apply video settings", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->FinalizeInitialization() == false)
		throw Exception("ERROR: Unable to apply video settings", __FILE__, __LINE__, __FUNCTION__);
	if (GUIManager->LoadMenuSkin("black_sleet", "img/menus/black_sleet_skin.png", "img/menus/black_sleet_texture.png") == false) {
		throw Exception("Failed to load the 'Black Sleet' MenuSkin images.", __FILE__, __LINE__, __FUNCTION__);
	}
	GUIManager->DEBUG_EnableGUIOutlines(false);

	if (VideoManager->Text()->LoadFont("img/fonts/libertine_capitals.ttf", "title20", 20) == false)
		throw Exception("Failed to load libertine_capitals.ttf font at size 20", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->Text()->LoadFont("img/fonts/libertine_capitals.ttf", "title22", 22) == false)
		throw Exception("Failed to load libertine_capitals.ttf font at size 22", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->Text()->LoadFont("img/fonts/libertine_capitals.ttf", "title24", 24) == false)
		throw Exception("Failed to load libertine_capitals.ttf font at size 24", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->Text()->LoadFont("img/fonts/libertine_capitals.ttf", "title28", 28) == false)
		throw Exception("Failed to load libertine_capitals.ttf font at size 28", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->Text()->LoadFont("img/fonts/libertine.ttf", "text18", 18) == false)
		throw Exception("Failed to load libertine.ttf font at size 18", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->Text()->LoadFont("img/fonts/libertine.ttf", "text20", 20) == false)
		throw Exception("Failed to load libertine.ttf font at size 20", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->Text()->LoadFont("img/fonts/libertine.ttf", "text22", 22) == false)
		throw Exception("Failed to load libertine.ttf font at size 22", __FILE__, __LINE__, __FUNCTION__);
	if (VideoManager->Text()->LoadFont("img/fonts/libertine.ttf", "text24", 24) == false)
		throw Exception("Failed to load libertine.ttf font at size 24", __FILE__, __LINE__, __FUNCTION__);
	VideoManager->Text()->SetDefaultStyle(TextStyle("text22", Color::white, VIDEO_TEXT_SHADOW_BLACK, 1, -2));
	if (GUIManager->SingletonInitialize() == false)
		throw Exception("ERROR: unable to initialize GUIManager", __FILE__, __LINE__, __FUNCTION__);
	SystemManager->InitializeTimers();
}

int main(int argc, char *argv[]) {
	atexit(QuitGame);
	try {
		// Change to the directory where the Allacrost data is stored
		#ifdef __MACH__
			string path;
			path = argv[0];
			// Remove the binary name
			path.erase(path.find_last_of('/'));
			// Remove the MacOS directory
			path.erase(path.find_last_of('/'));
			// Now the program should be in app/Contents
			path.append ("/Resources/");
			chdir(path.c_str());
		#elif (defined(__linux__) || defined(__FreeBSD__)) && !defined(RELEASE_BUILD)
			// Look for data files in DATADIR only if they are not available in the
			// current directory.
			if (ifstream("dat/config/settings.lua") == NULL)
				chdir(DATADIR);
		#endif
		// Initialize the random number generator (note: 'unsigned int' is a required usage in this case)
		srand(static_cast<unsigned int>(time(NULL)));
		// This variable will be set by the ParseProgramOptions function
		int32 return_code = EXIT_FAILURE;
		// Parse command lines and exit out of the game if needed
		if (ParseProgramOptions(return_code, static_cast<int32>(argc), argv) == false)
			return static_cast<int>(return_code);

		// Function call below throws exceptions if any errors occur
		InitializeEngine();

	} catch (Exception& e) {
		#ifdef WIN32
		MessageBox(NULL, e.ToString().c_str(), "Unhandled exception", MB_OK | MB_ICONERROR);
		#else
		cerr << e.ToString() << endl;
		#endif
		return EXIT_FAILURE;
	}

	ModeManager->Push(new BootMode());

	try {
		// This is the main loop for the game. The loop iterates once for every frame drawn to the screen.
		while (SystemManager->NotDone()) {
			// 1) Render the scene
			VideoManager->Clear();
			ModeManager->Draw();
			VideoManager->Display(SystemManager->GetUpdateTime());

			// 2) Process all new events
			InputManager->EventHandler();

			// 3) Update any streaming audio sources
			AudioManager->Update();

			// 4) Update timers for correct time-based movement operation
			SystemManager->UpdateTimers();

			// 5) Update the game status
			ModeManager->Update();

			// 6) Draw the FPS
			//GUISystem->DrawFPS(SystemManager->GetUpdateTime());
		} // while (SystemManager->NotDone())
	} catch (Exception& e) {
		#ifdef WIN32
		MessageBox(NULL, e.ToString().c_str(), "Unhandled exception", MB_OK | MB_ICONERROR);
		#else
		cerr << e.ToString() << endl;
		#endif
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

