#include "CXBOXController.h"
#include "Serial.h"
#include <iostream>

using namespace std;

CXBOXController* Player1;
wstring comID = L"\\\\.\\COM7"; //Make sure arduino IDE is closed if connected, the line is "busy" when the IDE is in use
LPCWSTR pls = comID.c_str();  //sending data is tricky
Serial* ser = new Serial(pls); //Create a serial object (Program uses serial communication at 9600 baud. Can be changed in Serial.h)

int main(int argc, char* argv[])
{
    Player1 = new CXBOXController(1);

    string buffer = "";

    while (true) {
        XINPUT_STATE state = Player1->GetState();

        if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START) {
            cout << "Start\n";
            Sleep(1000);
            buffer += "1";
        }
        if (state.Gamepad.sThumbLY > 10000) {
            cout << "Left Stick +Y\n";
            cout << state.Gamepad.sThumbLY;
            cout << "\n";
            Sleep(1000);
            buffer += "w";
        }
        if (state.Gamepad.sThumbLY < -10000) {
            cout << "Left Stick -Y\n";
            cout << state.Gamepad.sThumbLY;
            cout << "\n";
            Sleep(1000);
            buffer += "s";
        }
        if (state.Gamepad.sThumbLX < -10000) {
            cout << "Left Stick -X\n";
            cout << state.Gamepad.sThumbLX;
            cout << "\n";
            Sleep(1000);
            buffer += "a";
        }
        if (state.Gamepad.sThumbLX > 10000) {
            cout << "Left Stick +X\n";
            cout << state.Gamepad.sThumbLX;
            cout << "\n";
            Sleep(1000);
            buffer += "d";
        }  
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
            cout << "Y\n";
            Sleep(1000);
            buffer += "q";
        }
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
            cout << "A\n";
            Sleep(1000);
            buffer += "e";
        }
        if (state.Gamepad.sThumbRX < -10000) {
            cout << "Right Stick -X\n";
            cout << state.Gamepad.sThumbRX;
            cout << "\n";
            Sleep(1000);
            buffer += "j";
        }
        if (state.Gamepad.sThumbRX > 10000) {
            cout << "Right Stick +X\n";
            cout << state.Gamepad.sThumbRX;
            cout << "\n";
            Sleep(1000);
            buffer += "l";
        }
        if (state.Gamepad.sThumbRY > 10000) {
            cout << "Right Stick Y\n";
            cout << state.Gamepad.sThumbRY;
            cout << "\n";
            Sleep(1000);
            buffer += "i";
        }
        if (state.Gamepad.sThumbRY < -10000) {
            cout << "Right Stick Y\n";
            cout << state.Gamepad.sThumbRY;
            cout << "\n";
            Sleep(1000);
            buffer += "k";
        }
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
            cout << "Left Bumper\n";
            Sleep(1000);
            buffer += "u";
        }
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
            cout << "Right Bumper\n";
            Sleep(1000);
            buffer += "o";
        }
        if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) {
            break;
        }

        buffer += "v";

        ser->WriteData(buffer.c_str(), buffer.length());
        //cout << buffer + "\n";
        buffer.clear();

        Sleep(50);
    }

    delete(Player1);

    return(0);
}