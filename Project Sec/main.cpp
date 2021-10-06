#include <iostream>
#include <raylib.h>
#include <string>
#include <Python.h>

#include "TextBox.h"
#include "UI-Rectangle.h"

void executePythonScript(std::string input)
{
    FILE* file;
    wchar_t* argv[2];
    int argc = 2;

    std::wstring widestr = std::wstring(input.begin(), input.end());

    // normaal is het eerste argument 'python' maar omdat we het via een functie callen
    // is het eerste argument leeg en crashed het programma, vandaar dat we gewoon een tweede
    // argument zelf toevoegen :)
    argv[0] = const_cast<wchar_t*>(L"Python");
    argv[1] = const_cast<wchar_t*>(widestr.c_str());

    fopen_s(&file, "Scripts/emailsender.py", "r");
    if (file == NULL) return;
    PySys_SetArgv(argc, argv);
    PyRun_SimpleFile(file, "Scripts/emailsender.py");
    fclose(file);
}

void handleMouseInteraction(const Vector2& mouse, UIRect& button, std::string input)
{
    if (button.isPointIn(mouse))
        button.setOutlineColor(BLUE);
    else
    {
        button.setOutlineColor(BLACK);
        return; // als muis niet over button hovered gaat die er ook niet op klikken, dus we kunnen leaven
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && button.isPointIn(mouse))
    {
        if (input.size() > 3)
            executePythonScript(input);
        button.setBackgroundColor(BLUE);
    }
    else
        button.setBackgroundColor(WHITE);
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    std::string input;
    
    // onze textbox
    const float boxLength = 400, boxHeight = 40;
    TextBox textbox({ (screenWidth - boxLength) / 2.f, (screenHeight - boxHeight) / 2.f, boxLength, boxHeight });

    // de button
    const float buttonLength = 125.f, buttonHeight = 40.f;
    UIRect button({ (screenWidth - buttonLength) / 2.f, (screenHeight + boxHeight * 2) / 2.f }, {buttonLength, buttonHeight});

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
        const Vector2 mouse = GetMousePosition();

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

        handleMouseInteraction(mouse, button, input);

        textbox.setString(input);
        
        if (IsKeyPressed(KEY_ENTER) && input.size() > 3)
            executePythonScript(input);

        BeginDrawing();
        
        ClearBackground({50,50,50,255});
        DrawText("IC202A Spam bot", screenWidth / 2 - 50 * 4, 50, 50, WHITE);
        textbox.draw();
        button.draw();
        DrawText("Spam E-mail", button.getPosition().x + 5, button.getPosition().y + 10, 20, BLACK);
        EndDrawing();
    }

    Py_Finalize();
    CloseWindow();
   
    return 0;
}
