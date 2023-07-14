#include <Novice.h>
#include "Grid.h"
#include "Collision.h"
#include<imgui.h>


const char kWindowTitle[] = "LD2A_トリヤマ_ミヒロ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Sphere sphere;
	sphere.center = { 0,0,0 };
	sphere.radius = 1;

	Sphere sphere2;
	sphere2.center = { 2,0,2 };
	sphere2.radius = 1;

	Plane plane;
	plane.distance = 1;
	plane.normal = { 0,1,0 };
	plane.normal = Normalize(plane.normal);

	Segment segment;
	segment.origin = { 0,0,0 };
	segment.diff = { 1,1,1 };
	uint32_t color=WHITE;

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };

	Vector3 rotate{};

	Vector3 translate{};

	Vector3 cameraPosition{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Matrix4x4 worldMatrix = MakeAffinMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffinMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		Vector3 start = Transform(Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewportMatrix);
		//線分の移動
		if (keys[DIK_W]) {
			segment.origin.y += 0.1f;
		}
		if (keys[DIK_A]) {
			segment.origin.x -= 0.1f;
		}
		if (keys[DIK_S]) {
			segment.origin.y -= 0.1f;
		}
		if (keys[DIK_D]) {
			segment.origin.x += 0.1f;
		}
		//カメラの移動
		if (keys[DIK_DOWN]) {
			cameraPosition.y -= 0.1f;
		}
		if (keys[DIK_LEFT]) {
			cameraPosition.x -= 0.1f;
		}
		if (keys[DIK_UP]) {
			cameraPosition.y += 0.1f;
		}
		if (keys[DIK_RIGHT]) {
			cameraPosition.x += 0.1f;
		}
		if (keys[DIK_Z]) {
			cameraPosition.z += 0.1f;
		}
		if (keys[DIK_X]) {
			cameraPosition.z -= 0.1f;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, color);
		// 
		//線と平面の当たり判定
		if (IsCollisionSeP(segment,plane)) {
			Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), RED);
		}
		else {
			Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);
		}

		//球と平面の当たり判定
		if (IsCollisionSpP(sphere, plane)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate", &translate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("Line", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("PlaneCenter", &plane.normal.x, 0.01f);

		ImGui::End();
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
