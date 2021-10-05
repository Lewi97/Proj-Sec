#include <iostream>
#include <raylib.h>
#include <string>
#include <Python.h>

#include "TextBox.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    FILE* file;
    std::string input;
    
    // onze textbox
    float length = 400, height = 40;
    TextBox textbox({ (screenWidth - length) / 2.f, (screenHeight - height) / 2.f, length, height });

    // aantal argumenten
    int argc = 2;

    // eerste filler argument
    const wchar_t* arg = L"hello from cpp";

    wchar_t* argv[2];

    argv[0] = const_cast<wchar_t*>(arg);

    // start python
    Py_Initialize();
    InitWindow(screenWidth, screenHeight, "Spam spam spam");

    // we hebben geen gigatriljoen fps nodig
    SetTargetFPS(20);

    // clear raylib debug troep
    system("cls");

    while (!WindowShouldClose())
    {
        int key = GetCharPressed();

        // Check of er daadwerkelijk wordt getypt
        while (key > 0)
        {
            // accepteer alleen toetsen dus 32 - 125, we willen alleen printable characters
            if ((key >= 32) && (key <= 125))
                input += (char)key;

            key = GetCharPressed();  // meedere toetsen in 1 frame? pak de volgende

        }

        if (IsKeyDown(KEY_BACKSPACE) && input.size() > 0)
            input.pop_back();

        textbox.setString(input);
        
        if (IsKeyPressed(KEY_ENTER) && input.size() > 3)
        {
            std::wstring widestr = std::wstring(input.begin(), input.end());

            argv[1] = const_cast<wchar_t*>(widestr.c_str());

            fopen_s(&file, "Scripts/emailsender.py", "r");
            PySys_SetArgv(argc, argv);
            PyRun_SimpleFile(file, "Scripts/emailsender.py");
        }

        BeginDrawing();
        
        ClearBackground({50,50,50,255});
        textbox.draw();

        EndDrawing();
    }

    Py_Finalize();
    CloseWindow();
   
    return 0;
}
