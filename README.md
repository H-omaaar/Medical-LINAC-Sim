# Medical-LINAC-Sim
Geant4-based simulation of a Linear Accelerator (LINAC) for medical applications.


The primary goal of this project is to simulate and analyze the design and performance of a LINAC, focusing on its components and their interactions within a medical radiation treatment setting.
Key Features
Simulation of LINAC Components:

    Electron Gun: Models the generation and acceleration of electrons, simulating their behavior as they travel through the accelerator.
    Accelerator Waveguide: Simulates the waveguide where electrons are accelerated.
    Bending Magnet: Models the magnetic field that bends the electron beam.
    Treatment Head: Includes components like the X-ray target, flattening filter, scattering foil, collimators, and multi-leaf collimator (MLC) to simulate the final beam shaping and delivery for treatment.

Detailed Particle Interactions:

    Physics Processes: Uses GEANT4’s physics engine to simulate particle interactions, including energy deposition and scattering within the LINAC components. This helps in understanding how the LINAC's design impacts the radiation dose delivered.

Geometries and Materials:

    Component Modeling: Each LINAC component is modeled with specific geometric and material properties, such as the tungsten target, lead filter, and aluminum collimator. These models help in assessing the performance and efficiency of the LINAC.

    World Volume: Encloses the entire LINAC setup, ensuring accurate tracking of particle interactions within the simulation environment.

Physics Processes:

    Particle Tracking: Simulates the trajectories and interactions of electrons and other particles within the LINAC components.
    Energy Deposition: Calculates the energy deposited in various components, essential for determining the effectiveness of the LINAC in delivering a precise dose of radiation.

Optimization of LINAC Design:

    Adjustable Parameters: Allows for tweaking the design parameters, such as component sizes and materials, to optimize the LINAC’s performance and efficiency.

Data Analysis and Visualization:

    Output Data: Records simulation results, including energy deposition and particle tracking, for detailed post-processing and analysis.
    Visualization: Includes macros for visualizing the LINAC setup and particle interactions, aiding in the inspection and validation of the simulation.

CMake Configuration (CMakeLists.txt):

    Build System: Configures the build system to locate and use GEANT4 libraries, set up directories, compiler flags, and create the executable LinacSimulation.

Main Program (main.cc):

    Initialization: Initializes the run manager, sets up the detector construction, physics list, and primary generator actions.
    Visualization: Configures the visualization manager and user interface, executing the visualization macro for graphical representation.

Visualization Macro (vis.mac):

    Environment Setup: Defines the visualization environment, including camera viewpoints and zoom levels. Configures the display of geometries and particle tracks.

Detector Construction (DetectorConstruction.cc/hh):

    Geometry and Materials: Constructs the world volume and LINAC components, assigning material properties and visualization attributes.

Physics List (PhysicsList.cc/hh):

    Physics Processes: Registers relevant physics processes, including particle interactions and energy deposition, ensuring accurate modeling.

Primary Generator Action (PrimaryGeneratorAction.cc/hh):

    Particle Gun: Defines the parameters for particle emission, including energy, direction, and position.

Action Initialization (ActionInitialization.cc/hh):

    Action Management: Manages the initialization of primary generator actions for the simulation.

CMake Configuration (CMakeLists.txt):

    Build System: Sets up the build system for GEANT4, including configuration for directories and compiler flags.

This comprehensive simulation provides valuable insights into the LINAC’s design and performance, aiding in the development of more effective medical radiation treatment systems.
