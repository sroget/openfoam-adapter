#!/bin/bash

blockMesh
touch solid-openfoam.foam

# Compile boundary condition
(cd solidDisplacementFoamForce && wmake libso)

/home/sergio/tutorials/tools/run-openfoam.sh "$@"
. /home/sergio/tutorials/tools/openfoam-remove-empty-dirs.sh && openfoam_remove_empty_dirs
