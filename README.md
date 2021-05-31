# FMU-Unreal-Engine-Project
The Unreal Engine project using the FMU plugin
## Background
The goal of this project was to show a fmu simulated in the unreal engine as a proof of concept. 
The repository includes an already functional drone model with one level being normal gameplay and another incomplete level using VR elements.
The model was created using Dymola and instructions on how to make such a project from scratch will be included in this file.
## How to use the plugin
The Unreal-FMI plugin was created by Scott Greenwood of Oak Ridge National Laboratories and the most recent version is located [here](https://github.com/ORNL-Modelica/UnrealEngine-FMIPlugin).
Alternatively you can use the plugin included in the project. Just transfer the plugin folder from the original project to the next one.
## Making the project from scratch
### Setting up the project:

1. Create a new project, you can use any template, but it must be a c++ project and Not a blueprint.
2. In the file explorer find the plugins folder in project folder and if there isn’t one create a new folder and name it ”plugins”.
3. Find the FMIKit folder in the directory that looks something like this “UnrealEngine-FMIPlugin-master\FMIPlugin\Plugins” from the downloaded files.
Now copy and paste it into the plugins folder we just created.
4. This will let us use the plugin in the project, now go to edit>manage plugins to verify that it is there and that it is enabled
5. In the bottom right corner of the content browser click on the eye icon and check “show plugin content.”

### Exporting the FMU:

1. Select the model you wish to use go to the simulation tab and select translate>FMU
2. Check “cosimulation with dymola solvers” and make sure only 64 bit binaries are selected. The file will not simulate properly if the settings above are different.
3. Optional: to make things easier, you can copy the fmu file to the unreal project folder. It’s not necessary though.

### In the project:

1. Go to the C++ class FMIKit content folder and find the A_FMU class.
2. Make a blueprint object that is a child of the A_fmu class.
3. In the details window there is M path field, click on the ellipses next to it and navigate the browser to find the desired FMU.
4. Once the fmu file is selected, a list of state variables will appear and you can choose whch variable to keep track of.
5. The FMU will only give values to those variable, if you want the object to do anything based on those varaible you will need to program it.


## Using the Project as is:
The project has two levels, one with just the drone model and another with the drone model and VR components. Unfortunately the Vr Level does not include hand animations, it was crashing the project and I ran out of ime to fix it. Perhaps someone with better knowledge on c++ programming can fix it. In either level you can include a differen FMU and reprogram the blueprints to suit your needs for the project.

## If you have questions:
You can email me at jblewin100@gmail.com.
