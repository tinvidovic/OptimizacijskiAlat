# OptimizacijskiAlat

A solution written in C++ using the Google OR-Tools librbary that creates a Constraint Programming (CP) problem based on the input in the form of a dual-core embedded system application. The optimization engine then attempts to find a schedule for the embedded systems application with minimized inter-core data-propagation delays. The application is complete with a synthetic test generator.

## Setup

In order to use the solution the following steps are necessary:

1. Through the Visual Studio NuGet Package Manager fetch the latest stable version of Google OR-Tools
2. Preuzeti instalaciju or-tools na:
3. Add the path to \or-tools_VisualStudio2019-64bit_v8.0.8283\include to the Additional Include Directiories in Project Settings -> C/C++ 
4. Add the path to \or-tools_VisualStudio2019-64bit_v8.0.8283\lib to the Additional Library Dependencies in Project Settings -> Linker -> General
5. Add ortools.lib to the Additional Dependencies in Project Settings -> Linker -> Input
