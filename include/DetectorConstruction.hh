#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
private:
    G4LogicalVolume* fLogicWorld;
    G4LogicalVolume* ConstructElectronGun();
    G4LogicalVolume* ConstructAcceleratorWaveguide();
    G4LogicalVolume* ConstructBendingMagnet();
    G4LogicalVolume* ConstructTreatmentHead();
};

#endif
