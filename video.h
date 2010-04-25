
#ifndef __VIDEO_HEADER__
#define __VIDEO_HEADER__

#ifdef _WIN32
	#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include "defs.h"
#include "utils.h"

#include "color.h"

extern VideoEngine* VideoManager;

extern bool VIDEO_DEBUG;

const int32 VIDEO_ANIMATION_FRAME_PERIOD = 10;

enum {
	VIDEO_STANDARD_RES_WIDTH  = 1024,
	VIDEO_STANDARD_RES_HEIGHT = 768
};

void RotatePoint(float &x, float &y, float angle);

class VideoEngine {

public:
	~VideoEngine();

	bool SingletonInitialize();


	void SetTarget(VIDEO_TARGET target);

	void SetDrawFlags(int32 first_flag, ...);

	void Clear();

	void Clear(const Color& background_color);

	void Display(uint32 frame_time);

	bool CheckGLError()
		{ if (VIDEO_DEBUG == false) return false; _gl_error_code = glGetError(); return (_gl_error_code != GL_NO_ERROR); }

	GLenum GetGLError()
		{ return _gl_error_code; }

	const std::string CreateGLErrorString();

	int32 GetScreenWidth() const
		{ return _screen_width; }

	int32 GetScreenHeight() const
		{ return _screen_height; }

	bool IsInitialized() const
		{ return _initialized; }

	bool IsFullscreen() const
		{ return _fullscreen; }

	void SetResolution(uint32 width, uint32 height)
		{ _temp_width = width; _temp_height = height; }

	void SetFullscreen(bool fullscreen)
		{ _temp_fullscreen = fullscreen; }

	void ToggleFullscreen()
		{ SetFullscreen(!_temp_fullscreen); }

	void GetPixelSize(float& x, float& y);

	bool ApplySettings();

	void SetViewport(float left, float right, float bottom, float top);

	void GetDrawPosition(float &x, float &y) const
		{ x = _x_cursor; y = _y_cursor; }

	void Move(float x, float y);

	void MoveRelative(float x, float y);

	void PushMatrix()
		{ glPushMatrix(); }

	void PopMatrix()
		{ glPopMatrix(); }

	void PushState();

	void PopState ();

	void Rotate(float angle)
		{ glRotatef(angle, 0, 0, 1); }

	void Scale(float x, float y)
		{ glScalef(x, y, 1.0f); }

	void SetTransform(float matrix[16]);

	void FadeScreen(const Color& color, uint32 time)
		{ _screen_fader.BeginFade(color, time); }

	bool IsFading()
		{ return _screen_fader.IsFading(); }

	void DrawLine(float x1, float y1, float x2, float y2, float width, const Color& color);

	void DrawRectangle(float width, float height, const Color& color);

	void DrawRectangleOutline(float x1, float y1, float x2, float y2, float width, const Color& color);

	void MakeScreenshot(const std::string& filename = "screenshot.jpg");

	void ToggleAdvancedDisplay()
		{ _advanced_display = !_advanced_display; }

	bool SetDefaultCursor(const std::string& cursor_image_filename);

	void DrawFPS(uint32 frame_time);

	void ToggleFPS()
		{ _fps_display = !_fps_display; }
private:
	VideoEngine();

	bool _fps_display;

	uint32 _fps_sum;

	GLenum _gl_error_code;

	int32  _screen_width, _screen_height;

	bool _fullscreen;

	float _x_cursor, _y_cursor;

	char _next_temp_file[9];

	bool _advanced_display;

	int32 _num_draw_calls;

	std::list<private_video::ShakeForce> _shake_forces;

	bool _temp_fullscreen;

	int32 _temp_width;

	int32 _temp_height;

	int32 _animation_counter;

	int32 _current_frame_diff;

	std::stack<private_video::Context> _context_stack;

	bool _initialized;

	int32 _ConvertXAlign(int32 xalign);

	int32 _ConvertYAlign(int32 yalign);

	float _RoundForce(float force);

	int32 _ScreenCoordX(float x);

	int32 _ScreenCoordY(float y);

	void _DEBUG_ShowAdvancedStats();
};

#endif
