#include "DetectorConstruction.hh"
#include "G4SDManager.hh"
#include "SensitiveDetector.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"  // Include for G4Cons
#include "G4Torus.hh" // Include for G4Torus
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction(), fLogicWorld(nullptr) {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Define materials
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");
    G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");
    G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* aluminum = nist->FindOrBuildMaterial("G4_Al");
    G4Material* iron = nist->FindOrBuildMaterial("G4_Fe");

    // World volume
    G4double world_size = 3.0 * m;
    G4Box* solidWorld = new G4Box("World", world_size / 2, world_size / 2, world_size / 2);
    fLogicWorld = new G4LogicalVolume(solidWorld, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), fLogicWorld, "World", 0, false, 0);

    // Construct and place components
    G4LogicalVolume* electronGun = ConstructElectronGun();
    new G4PVPlacement(0, G4ThreeVector(0, 0, -1.45 * m), electronGun, "ElectronGun", fLogicWorld, false, 0);

    G4LogicalVolume* waveguide = ConstructAcceleratorWaveguide();
    new G4PVPlacement(0, G4ThreeVector(0, 0, -0.45 * m), waveguide, "Waveguide", fLogicWorld, false, 0);

    G4LogicalVolume* bendingMagnet = ConstructBendingMagnet();
    new G4PVPlacement(0, G4ThreeVector(0.5 * m, 0, 0.5 * m), bendingMagnet, "BendingMagnet", fLogicWorld, false, 0);

    G4LogicalVolume* treatmentHead = ConstructTreatmentHead();
    new G4PVPlacement(0, G4ThreeVector(0.5 * m, 0, 1.5 * m), treatmentHead, "TreatmentHead", fLogicWorld, false, 0);

    return physWorld;
}

G4LogicalVolume* DetectorConstruction::ConstructElectronGun() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");
    G4Tubs* solidElectronGun = new G4Tubs("ElectronGun", 0, 1 * cm, 5 * cm, 0, 360 * deg);
    G4LogicalVolume* logicElectronGun = new G4LogicalVolume(solidElectronGun, tungsten, "ElectronGun");
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // Green
    logicElectronGun->SetVisAttributes(visAttributes);
    return logicElectronGun;
}

G4LogicalVolume* DetectorConstruction::ConstructAcceleratorWaveguide() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");
    G4Tubs* solidWaveguide = new G4Tubs("Waveguide", 0, 0.5 * cm, 50 * cm, 0, 360 * deg);
    G4LogicalVolume* logicWaveguide = new G4LogicalVolume(solidWaveguide, copper, "Waveguide");
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0)); // Blue
    logicWaveguide->SetVisAttributes(visAttributes);
    return logicWaveguide;
}

G4LogicalVolume* DetectorConstruction::ConstructBendingMagnet() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* iron = nist->FindOrBuildMaterial("G4_Fe");
    // Adjusted parameters: pRtor > pRmax
    G4double sweptRadius = 1.0 * m;
    G4double outerRadius = 0.5 * m;
    G4Torus* solidBendingMagnet = new G4Torus("BendingMagnet", 0, outerRadius, sweptRadius, 0, 270 * deg);
    G4LogicalVolume* logicBendingMagnet = new G4LogicalVolume(solidBendingMagnet, iron, "BendingMagnet");
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Red
    logicBendingMagnet->SetVisAttributes(visAttributes);
    return logicBendingMagnet;
}

G4LogicalVolume* DetectorConstruction::ConstructTreatmentHead() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* tungsten = nist->FindOrBuildMaterial("G4_W");
    G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* aluminum = nist->FindOrBuildMaterial("G4_Al");

    // Treatment head container
    G4double head_size = 20 * cm;
    G4Box* solidHead = new G4Box("TreatmentHead", head_size / 2, head_size / 2, head_size / 2);
    G4LogicalVolume* logicHead = new G4LogicalVolume(solidHead, aluminum, "TreatmentHead");

    // X-ray target
    G4double target_thickness = 1 * mm;
    G4double target_radius = 1 * cm;
    G4Tubs* solidTarget = new G4Tubs("Target", 0, target_radius, target_thickness / 2, 0, 360 * deg);
    G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, tungsten, "Target");
    new G4PVPlacement(0, G4ThreeVector(0, 0, -9 * cm), logicTarget, "Target", logicHead, false, 0);

    // Flattening filter
    G4double filter_base_diameter = 3 * cm;
    G4double filter_height = 1 * cm;
    G4Cons* solidFilter = new G4Cons("Filter", 0, filter_base_diameter / 2, 0, filter_base_diameter / 2, filter_height / 2, 0, 360 * deg);
    G4LogicalVolume* logicFilter = new G4LogicalVolume(solidFilter, lead, "Filter");
    new G4PVPlacement(0, G4ThreeVector(0, 0, -7 * cm), logicFilter, "Filter", logicHead, false, 0);

    // Scattering foil
    G4double foil_thickness = 0.1 * mm;
    G4double foil_radius = 1 * cm;
    G4Tubs* solidFoil = new G4Tubs("Foil", 0, foil_radius, foil_thickness / 2, 0, 360 * deg);
    G4LogicalVolume* logicFoil = new G4LogicalVolume(solidFoil, aluminum, "Foil");
    new G4PVPlacement(0, G4ThreeVector(0, 0, -5 * cm), logicFoil, "Foil", logicHead, false, 0);

    // Primary collimator
    G4double collimator_radius = 5 * cm;
    G4double collimator_thickness = 2 * cm;
    G4Tubs* solidCollimator = new G4Tubs("Collimator", 0, collimator_radius, collimator_thickness / 2, 0, 360 * deg);
    G4LogicalVolume* logicCollimator = new G4LogicalVolume(solidCollimator, tungsten, "Collimator");
    new G4PVPlacement(0, G4ThreeVector(0, 0, -3 * cm), logicCollimator, "Collimator", logicHead, false, 0);

    // Multi-leaf collimator (MLC)
    G4double leaf_width = 5 * mm;
    G4double leaf_height = 10 * cm;
    G4double leaf_thickness = 0.5 * cm;
    G4Box* solidLeaf = new G4Box("Leaf", leaf_width / 2, leaf_height / 2, leaf_thickness / 2);
    G4LogicalVolume* logicLeaf = new G4LogicalVolume(solidLeaf, tungsten, "Leaf");

    // Ensure the leaf positions are within the head_size bounds
    G4double maxLeafPosition = (head_size - leaf_thickness) / 2;
    for (int i = 0; i < 120; ++i) {
        G4double position = -collimator_radius + (i + 0.5) * leaf_width;
        if (std::abs(position) < maxLeafPosition) {
            new G4PVPlacement(0, G4ThreeVector(position, 0, 1 * cm), logicLeaf, "Leaf", logicHead, false, i);
        }
    }

    return logicHead;
}
