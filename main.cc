#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4Version.hh"
#include "G4VisExecutive.hh"
#if  G4VERSION_NUMBER>=930
#include "G4UIExecutive.hh"
#else
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#endif
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "ActionInitialization.hh"
#include "SensitiveDetector.hh"
#include "QGSP_BERT.hh"

int main(int argc, char** argv)
{
    // Run manager
    G4RunManager* runManager = new G4RunManager();

    // mandatory Initialization classes 
    G4VUserDetectorConstruction* detector = new DetectorConstruction();
    runManager->SetUserInitialization(detector);

    G4VUserPhysicsList* physics = new PhysicsList();
    runManager->SetUserInitialization(physics);

    // mandatory User Action classes
    runManager->SetUserInitialization(new ActionInitialization());

    // Initialize G4 kernel
    runManager->Initialize();

    // Initialize the visualization manager
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc != 1) {  // batch mode  
        // command line contains name of the macro to execute
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else {  // interactive mode : define UI session
#if  G4VERSION_NUMBER >= 930
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute ../vis.mac");
#else
        // Older versions of G4: UI selected by user
#ifdef G4UI_USE_TCSH
        G4UIsession* ui = new G4UIterminal(new G4UItcsh);
#else
        G4UIsession* ui = new G4UIterminal();
#endif
        UImanager->ApplyCommand("/control/execute ../vis.mac");
#endif
        ui->SessionStart();
        delete ui;
    }

    delete runManager;
    return 0;
}

