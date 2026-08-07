#include "GUI.h"
#include "Scheduler.h"
#include "Doctor.h"
#include "Patient.h"
#include "raylib.h"

GUI::GUI(SimulationEngine* simulationEngine)
{
    engine = simulationEngine;
    running = false;
    finished = false;
}

void GUI::Run()
{
    InitWindow(1200, 700, "Clinic Simulation");

    double lastStep = GetTime();

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        Rectangle startButton = { 40, 100, 180, 55 };
        Rectangle pauseButton = { 240, 100, 180, 55 };
        Rectangle stepButton = { 440, 100, 180, 55 };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, startButton))
        {
            if (!finished)
            {
                running = true;
                lastStep = GetTime();
            }
        }

   
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, pauseButton))
        {
            running = false;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, stepButton))
        {
            if (!finished)
            {
                bool success = engine->Step();

                if (!success)
                {
                    finished = true;
                    running = false;
                }
            }
        }


        if (running && !finished)
        {
            double now = GetTime();

            if (now - lastStep >= 0.5)
            {
                bool success = engine->Step();

                if (!success)
                {
                    finished = true;
                    running = false;
                }

                lastStep = now;
            }
        }

      

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(
            "CLINIC SIMULATION",
            40,
            25,
            35,
            DARKBLUE
        );

        DrawText(
            "Time:",
            900,
            35,
            25,
            BLACK
        );

        DrawText(
            TextFormat("%d", engine->getCurrentTimestamp()),
            980,
            35,
            25,
            DARKBLUE
        );

   
        DrawRectangleRec(startButton, DARKGREEN);
        DrawText("START", 95, 117, 24, WHITE);

        DrawRectangleRec(pauseButton, ORANGE);
        DrawText("PAUSE", 292, 117, 24, WHITE);

        DrawRectangleRec(stepButton, DARKBLUE);
        DrawText("STEP", 505, 117, 24, WHITE);


        DrawText("Status:", 650, 115, 22, BLACK);

        if (finished)
        {
            DrawText("FINISHED", 730, 115, 22, RED);
        }
        else if (running)
        {
            DrawText("RUNNING", 730, 115, 22, GREEN);
        }
        else
        {
            DrawText("PAUSED", 730, 115, 22, ORANGE);
        }


        DrawText(
            "DOCTORS",
            40,
            190,
            28,
            DARKBLUE
        );

        int doctorY = 235;

        schedular* scheduler = engine->getScheduler();

        for (int i = 0; i < scheduler->getDoctorCount(); i++)
        {
            doctor* d = scheduler->getDoctor(i);

            DrawRectangle(
                40,
                doctorY,
                520,
                65,
                LIGHTGRAY
            );

            DrawText(
                TextFormat(
                    "Dr %c%d",
                    d->get_docspec(),
                    d->get_id()
                ),
                55,
                doctorY + 10,
                22,
                BLACK
            );

            DrawText(
                TextFormat(
                    "Branch: %d",
                    d->get_branch()
                ),
                160,
                doctorY + 10,
                20,
                DARKGRAY
            );

            if (d->get_cs() == idle)
            {
                DrawText(
                    "FREE",
                    55,
                    doctorY + 35,
                    18,
                    GREEN
                );
            }
            else if (d->get_cs() == busy)
            {
                DrawText(
                    TextFormat(
                        "BUSY until %d",
                        d->get_et()
                    ),
                    55,
                    doctorY + 35,
                    18,
                    RED
                );

                if (d->get_current_patient() != nullptr)
                {
                    DrawText(
                        TextFormat(
                            "Patient: %d",
                            d->get_current_patient()->getId()
                        ),
                        300,
                        doctorY + 35,
                        18,
                        DARKBLUE
                    );
                }
            }
            else if (d->get_cs() == onbreak)
            {
                DrawText(
                    TextFormat(
                        "BREAK until %d",
                        d->get_eb()
                    ),
                    55,
                    doctorY + 35,
                    18,
                    ORANGE
                );
            }
            else if (d->get_cs() == shift_not_started)
            {
                DrawText(
                    "SHIFT NOT STARTED",
                    55,
                    doctorY + 35,
                    18,
                    GRAY
                );
            }

            doctorY += 75;
        }


        DrawRectangle(
            620,
            190,
            520,
            250,
            LIGHTGRAY
        );

        DrawText(
            "SIMULATION INFORMATION",
            645,
            215,
            25,
            DARKBLUE
        );

        DrawText(
            TextFormat(
                "Current Timestamp: %d",
                engine->getCurrentTimestamp()
            ),
            645,
            270,
            21,
            BLACK
        );

        DrawText(
            TextFormat(
                "Doctors: %d",
                scheduler->getDoctorCount()
            ),
            645,
            310,
            21,
            BLACK
        );

        DrawText(
            "STEP = advance one timestep",
            645,
            365,
            19,
            DARKGRAY
        );

        DrawText(
            "START = run automatically",
            645,
            395,
            19,
            DARKGRAY
        );

        DrawText(
            "ESC = close GUI",
            40,
            650,
            20,
            GRAY
        );

        EndDrawing();
    }

    CloseWindow();
}