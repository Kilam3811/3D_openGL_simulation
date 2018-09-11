#include "XBoxController.h"
#include <cmath>
#define MAX_DEAD_ZONE_VALUE 32767
GamePad::XBoxController::XBoxController(XInputWrapper * xinput, DWORD id)
{
	//This refers to the address of the object then dereference it.
	//This will let the input argument to the class member variable xinput
	this->xinput = xinput;
	this->Player_ID = id;
}

DWORD GamePad::XBoxController::GetControllerId()
{
	return this->Player_ID;
}

bool GamePad::XBoxController::IsConnected()
{
	DWORD Result;
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Store the return value of function 
	//If it is ERROR_SUCCESS then the joystick is connected
	Result = xinput->XInputGetState(Player_ID, &state);
	if (Result == ERROR_SUCCESS) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedA()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the spcifice controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedB()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedX()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedY()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the spcifice controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedLeftShoulder()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the spcifice controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedRightShoulder()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedLeftDpad()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedRightDpad()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedUpDpad()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedDownDpad()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedStart()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedBack()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedLeftThumb()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) {
		return TRUE;
	}
	return FALSE;
}

bool GamePad::XBoxController::PressedRightThumb()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) {
		return TRUE;
	}
	return FALSE;
}

BYTE GamePad::XBoxController::LeftTriggerLocation()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	return state.Gamepad.bLeftTrigger;
}

BYTE GamePad::XBoxController::RightTriggerLocation()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	return state.Gamepad.bRightTrigger;
}

GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);

	//Get the value of antual x and y in state struct
	SHORT Lx = state.Gamepad.sThumbLX;
	SHORT Ly = state.Gamepad.sThumbLY;

	//Calculate the magnitude of x and y and see if it is within the dead zone
	double magnitude = sqrt(Lx * Lx + Ly * Ly);
	//The magnitude would greater than MAX_DEAD_ZONE_VALUE but just set that value be the max which is 32767
	if (magnitude > Dead_zone_radius) {
		if (magnitude > MAX_DEAD_ZONE_VALUE) {
			magnitude = MAX_DEAD_ZONE_VALUE;
		}
		//The phase of the x and y in order to resolve it to two components
		double angle = atan2(Ly, Lx);

		//The relative magnitude which relative to the end of the dead zone
		double relative_magnitude = magnitude - Dead_zone_radius;

		//The part that which will be scaled in terms of 0..MAX
		double ratio_ralative_magnitude = relative_magnitude / (MAX_DEAD_ZONE_VALUE - Dead_zone_radius);
		//Lastly,finaly scaled/modified magnitude would the ratio times MAX_DEAD_ZONE_VALUE
		double modified_magnitude = ratio_ralative_magnitude * MAX_DEAD_ZONE_VALUE;

		//Resolve it in to x and y components
		SHORT Lx_Modified = (SHORT)(modified_magnitude * cos(angle));
		SHORT Ly_Modified = (SHORT)(modified_magnitude * sin(angle));
		return GamePad::Coordinate(Lx_Modified, Ly_Modified);
	}
	//If it is whithin the dead zone then returning [0,0]
	return GamePad::Coordinate(0, 0);
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation()
{
	XINPUT_STATE state;
	//Clear out memory
	ZeroMemory(&state, sizeof(state));
	//Get the state of the specific controller
	xinput->XInputGetState(Player_ID, &state);
	SHORT Rx = state.Gamepad.sThumbRX;
	SHORT Ry = state.Gamepad.sThumbRY;
	//Calculate the magnitude of x and y and see if it is within the dead zone
	double magnitude = sqrt(Rx*Rx + Ry * Ry);
	if (magnitude > Dead_zone_radius) {
		//The magnitude would greater than MAX_DEAD_ZONE_VALUE but just set that value be the max which is 32767
		if (magnitude > MAX_DEAD_ZONE_VALUE) {
			magnitude = MAX_DEAD_ZONE_VALUE;
		}
		//The phase of the x and y in order to resolve it to two components
		double angle = atan2(Ry, Rx);

		//The relative magnitude which relative to the end of the dead zone
		double relative_magnitude = magnitude - Dead_zone_radius;

		//The part that which will be scaled in terms of 0..MAX
		double ratio_ralative_magnitude = relative_magnitude / (MAX_DEAD_ZONE_VALUE - Dead_zone_radius);

		//Lastly,finaly scaled/modified magnitude would the ratio times MAX_DEAD_ZONE_VALUE
		double modified_magnitude = ratio_ralative_magnitude * MAX_DEAD_ZONE_VALUE;

		//Resolve it in to x and y components
		SHORT Rx_Modified = (SHORT)(modified_magnitude * cos(angle));
		SHORT Ry_Modified = (SHORT)(modified_magnitude * sin(angle));
		return GamePad::Coordinate(Rx_Modified, Ry_Modified);
	}
	//If it is whithin the dead zone then returning [0,0]
	return GamePad::Coordinate(0, 0);

}

void GamePad::XBoxController::Vibrate(WORD left, WORD right)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = left; // use any value between 0-65535 here
	vibration.wRightMotorSpeed = right; // use any value between 0-65535 here
	XInputSetState(Player_ID, &vibration);
}

void GamePad::XBoxController::SetDeadzone(unsigned int radius)
{
	//User define dead zone
	Dead_zone_radius = radius;
}
