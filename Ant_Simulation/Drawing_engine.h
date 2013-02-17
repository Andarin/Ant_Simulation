#pragma once
#include <memory>
#include "general_constants.h"
#include "Ant_Sim.h"

class Ant_Sim;

class Drawing_engine
{
public:
	Drawing_engine(Ant_Sim*, int);
	~Drawing_engine(void);

	void render(void);

private:
	Ant_Sim *_ant_sim_ptr;
	int _cam_velocity;
	int _recent_cam_velocity;
	Camera _camera;

	bool _mousein;
	bool _countdown_on;
	bool _high_quality_on;
	bool _switch_fog_on;

	SDL_Surface *_prescreen;
	SDL_Surface *_screen;
	SDL_Surface *_logo;
	unsigned int _tex_board;
	unsigned int _tex_border;
	unsigned int _tex_colony;
	unsigned int _tex_box;
	unsigned int _tex_apple_side;
	unsigned int _tex_apple_top;
	unsigned int _tex_logo;
	unsigned int _tex_result;
	unsigned int _tex_result_pointer;
	glfont::GLFont _screen_text;
	MeshObj* _ant_hq_array[8];
	Uint8 *_keystates;

	// methods
	void set_window(void);
	void set_openGL(void);
	void set_fog(void);
	void load_textures(void);
	void load_hq_ants(void);
	void init(void);
	void switch_to_normal_perspective(int);
	void switch_to_ortho_perspective(void);
	void draw_text(std::string, float, float);
	void draw_text_with_number(std::string, int, float, float);
	void draw_text_with_number(std::string, double, float, float);
	void draw_countdown(int);
	void draw_result(void);
	void draw_hud(Uint32);
	void display(Uint32, int);
	void clean_up(void);
	void start_countdown(void);
};