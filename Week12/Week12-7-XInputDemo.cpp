#include <iostream>
#include <Windows.h>
#include <Xinput.h>

using std::cout;
using std::endl;

#pragma once
#pragma comment(lib, "XInput.lib")

class Gamepad
{
private:
	int cId;
	XINPUT_STATE state;

	float deadzoneX;
	float deadzoneY;

public:
	Gamepad() : deadzoneX(0.05f), deadzoneY(0.02f) {}
	Gamepad(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {}

	float leftStickX;
	float leftStickY;
	float rightStickX;
	float rightStickY;
	float leftTrigger;
	float rightTrigger;

	int  GetPort();
	XINPUT_GAMEPAD* GetState();
	bool CheckConnection();
	bool Refresh();
	bool IsPressed(WORD);
};

int Gamepad::GetPort()
{
	return cId + 1;
}

XINPUT_GAMEPAD* Gamepad::GetState()
{
	return &state.Gamepad;
}

bool Gamepad::CheckConnection()
{
	int controllerId = -1;

	for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &state) == ERROR_SUCCESS)
			controllerId = i;
	}

	cId = controllerId;

	return controllerId != -1;
}

// Returns false if the controller has been disconnected
bool Gamepad::Refresh()
{
	if (cId == -1)
		CheckConnection();

	if (cId != -1)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(cId, &state) != ERROR_SUCCESS)
		{
			cId = -1;
			return false;
		}

		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

		leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
		leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

		if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

		rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
		rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

		if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
		if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

		leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
		rightTrigger = (float)state.Gamepad.bRightTrigger / 255;

		return true;
	}
	return false;
}

bool Gamepad::IsPressed(WORD button)
{
	return (state.Gamepad.wButtons & button) != 0;
}

int main()
{
	Gamepad gamepad;

	bool wasConnected = true;

	while (true)
	{
		Sleep(100);

		if (!gamepad.Refresh())
		{
			if (wasConnected)
			{
				wasConnected = false;

				cout << "Please connect an Xbox controller." << endl;
			}
		}
		else
		{
			if (!wasConnected)
			{
				wasConnected = true;

				cout << "Controller connected on port " << gamepad.GetPort() << endl;
			}

			if (gamepad.leftStickX != 0.0f || gamepad.leftStickY != 0.0f || gamepad.rightStickX != 0.0f || gamepad.rightStickY != 0.0f)
			{
				cout << "Left thumb stick: (" << gamepad.leftStickX << ", " << gamepad.leftStickY << ")   Right thumb stick : (" << gamepad.rightStickX << ", " << gamepad.rightStickY << ")" << endl;
			}

			if (gamepad.leftTrigger != 0.0f || gamepad.rightTrigger != 0.0f)
			{
				cout << "Left analog trigger: " << gamepad.leftTrigger << "   Right analog trigger: " << gamepad.rightTrigger << endl;
			}

			if (gamepad.IsPressed(XINPUT_GAMEPAD_A)) cout << "(A) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_B)) cout << "(B) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_X)) cout << "(X) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_Y)) cout << "(Y) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_DPAD_UP)) cout << "(UP) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_DPAD_DOWN)) cout << "(DOWN) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_DPAD_LEFT)) cout << "(LEFT) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT)) cout << "(RIGHT) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_START)) cout << "(START) button pressed" << endl;
			if (gamepad.IsPressed(XINPUT_GAMEPAD_BACK)) cout << "(BACK) button pressed" << endl;


		}
	}
}