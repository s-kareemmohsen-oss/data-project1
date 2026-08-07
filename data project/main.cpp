#include <iostream>

#include "SimulationEngine.h"
#include "FileManager.h"
#include "GUI.h"

using namespace std;

int main()
{
    SimulationEngine simulation;
    FileManager fileManager;

    if (!fileManager.LoadInput("sample3.txt", &simulation))
    {
        cout << "Failed to load input file." << endl;
        return -1;
    }

    cout << "Input file loaded successfully." << endl;

    int choice;

    cout << endl;
    cout << "Select Run Mode:" << endl;
    cout << "1. Silent Mode" << endl;
    cout << "2. Interactive Mode" << endl;
    cout << "3. GUI Mode" << endl;
    cout << "Enter choice: ";

    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        simulation.RunSilent();
    }
    else if (choice == 2)
    {
        simulation.RunInteractive();
    }
    else if (choice == 3)
    {
        GUI gui(&simulation);
        gui.Run();
    }
    else
    {
        cout << "Invalid choice." << endl;
        return -1;
    }

    
    fileManager.SaveOutput("output.txt", &simulation);

    cout << "Output file generated successfully." << endl;

    return 0;
}