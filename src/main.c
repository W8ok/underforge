// main.c
#include "main.h"

#define CAMERA_SPEED 10
#define SCROLL_SPEED 0.1f
#define MIN_ZOOM 0.1f
#define MAX_ZOOM 10.0f

static inline void _camera_update(Camera2D* camera)
{
	float wheel = GetMouseWheelMove();
	if (wheel != 0)
	{
		camera->zoom += wheel * SCROLL_SPEED;
		if (camera->zoom < MIN_ZOOM)
			camera->zoom = MIN_ZOOM;

		if (camera->zoom > MAX_ZOOM)
			camera->zoom = MAX_ZOOM;
	}

	float pan_speed = CAMERA_SPEED / camera->zoom; 
	if (IsKeyDown(KEY_W))
		camera->target.y -= pan_speed;
	if (IsKeyDown(KEY_A))
		camera->target.x -= pan_speed;
	if (IsKeyDown(KEY_S))
		camera->target.y += pan_speed;
	if (IsKeyDown(KEY_D))
		camera->target.x += pan_speed;

	camera->offset = (Vector2){ GetScreenWidth()*0.5f, GetScreenHeight()*0.5f };
}

static inline bool _app_init(AppContext* app)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Underforge");

	ToggleBorderlessWindowed();

	app->camera.target = (Vector2){ 0, 0 };
	app->camera.offset = (Vector2){ GetScreenWidth()*0.5f, GetScreenHeight()*0.5f };
	app->camera.rotation = 0.0f;
	app->camera.zoom = 1.0f;
    
    SetTargetFPS(60);

	return true;
}

static inline void _app_quit(AppContext* app)
{
	CloseWindow();
	if (app)
		free(app);
}

int main(void)
{
	AppContext* app = (AppContext*) calloc(1, sizeof(AppContext));
	if (!app)
		ERROR_EXIT("Memory Allocation Failure");

	_app_init(app);
    
    while (!WindowShouldClose())
    {
		//game_main();
		_camera_update(&app->camera);

        BeginDrawing();
        ClearBackground(BLACK);
		BeginMode2D(app->camera);

		//render_main();

		EndMode2D();

		//render_gui();

        EndDrawing();
    }

	_app_quit(app);
    return 0;
}
