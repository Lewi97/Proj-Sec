#include <iostream>
#include <raylib.h>
#include <string>
#include <Python.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    FILE* file;
    std::string input;

    fopen_s(&file, "Scripts/emailsender.py", "r");
    
    int argc = 2;

    const wchar_t* arg = L"hello from cpp";

    wchar_t* argv[2];

    argv[0] = const_cast<wchar_t*>(arg);

    Py_Initialize();
    InitWindow(screenWidth, screenHeight, "Spam spam spam");

    system("cls");

    while (!WindowShouldClose())
    {
        int key = GetCharPressed();

        // Check of er daadwerkelijk wordt getypt
        while (key > 0)
        {
            // accepteer alleen toetsen dus 32 - 125, we willen alleen printable characters
            if ((key >= 32) && (key <= 125))
            {
                input += (char)key;
            }

            key = GetCharPressed();  // meedere toetsen in 1 frame? pak de volgende
        }

        if (IsKeyPressed(KEY_BACKSPACE) && input.size() > 0)
            input.pop_back();

        if (IsKeyPressed(KEY_ENTER) && input.size() > 3)
        {
            // vraag me niet dit uit te leggen
            std::wstring widestr = std::wstring(input.begin(), input.end());

            argv[0] = const_cast<wchar_t*>(widestr.c_str());
            argv[1] = const_cast<wchar_t*>(widestr.c_str());

            fopen_s(&file, "Scripts/emailsender.py", "r");
            PySys_SetArgv(argc, argv);
            PyRun_SimpleFile(file, "Scripts/emailsender.py");
        }

        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawText(input.c_str(), 10, 10, 20, BLACK);

        EndDrawing();
    }

    Py_Finalize();
    CloseWindow();
   
    return 0;
}
