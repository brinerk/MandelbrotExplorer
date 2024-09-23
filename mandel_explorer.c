#include<raylib.h>
#include<complex.h>
#include<rlgl.h>
#include<raymath.h>
#include<stdio.h>

#define WIDTH 1920 
#define HEIGHT 1080

#define INT_HEIGHT 1080 * 1.78

int main(void) {

	InitWindow(WIDTH, HEIGHT, "Mandel");
	SetTargetFPS(60);
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetExitKey(KEY_Q);
	Shader shader = LoadShader(NULL, "mandel.fs");
	RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

	Vector2 resolution = { WIDTH, INT_HEIGHT };
	Vector2 center = {0.0f, 0.0f};

	float zoom = 1.0f;
	int max_iter = 100;
	int resolutionLoc = GetShaderLocation(shader, "resolution");
    int centerLoc = GetShaderLocation(shader, "center");
    int zoomLoc = GetShaderLocation(shader, "zoom");
    int maxIterLoc = GetShaderLocation(shader, "max_iter");
	//int res = GetShaderLocation(shader, "u_resolution");
	//int time = GetShaderLocation(shader, "u_time");
	//float test_time = 1.0;

	while (!WindowShouldClose()) {

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, (0.3f*zoom));
			center.x -= (delta.x / WIDTH) *4.0f ;
			center.y += (delta.y / HEIGHT) *4.0f ;
		}

		float wheelMovement = GetMouseWheelMove();
		if(wheelMovement) {
			zoom *= (wheelMovement >0) ? 0.7f : 1.3f;
		}

        if (IsKeyDown(KEY_W)) center.y -= 0.01f * zoom;
        if (IsKeyDown(KEY_S)) center.y += 0.01f * zoom;
        if (IsKeyDown(KEY_A)) center.x -= 0.01f * zoom;
        if (IsKeyDown(KEY_D)) center.x += 0.01f * zoom;
		//zoom *= (GetMouseWheelMove()*1);
        if (IsKeyDown(KEY_UP)) zoom *= 0.95f;
        if (IsKeyDown(KEY_DOWN)) zoom *= 1.05f;
        if (IsKeyDown(KEY_I)) max_iter += 1;
        if (IsKeyDown(KEY_K)) max_iter = (max_iter > 1) ? max_iter - 1 : 1;

        SetShaderValue(shader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, centerLoc, &center, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, maxIterLoc, &max_iter, SHADER_UNIFORM_INT);
        //SetShaderValue(shader, res, &resolution, SHADER_UNIFORM_VEC2);
        //SetShaderValue(shader, time, &test_time, SHADER_UNIFORM_FLOAT);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(shader);
		DrawTextureEx(target.texture, (Vector2){ 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
        EndShaderMode();

        EndDrawing();
	}
	UnloadShader(shader);
	CloseWindow();
	printf("Program Exiting\n");
	return 0;
}
