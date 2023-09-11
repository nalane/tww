//
// Generated by dtk
// Translation Unit: c_sxyz.cpp
//

#include "SSystem/SComponent/c_sxyz.h"
#include "dolphin/types.h"

const csXyz csXyz::Zero = csXyz(0, 0, 0);

/* 80245EAC-80245EBC       .text __ct__5csXyzFsss */
csXyz::csXyz(s16 param_0, s16 param_1, s16 param_2) {
    x = param_0;
    y = param_1;
    z = param_2;
}

/* 80245EBC-80245F14       .text __pl__5csXyzFR5csXyz */
csXyz csXyz::operator+(csXyz& param_0) {
    return csXyz(x + param_0.x, y + param_0.y, z + param_0.z);
}

/* 80245F14-80245F48       .text __apl__5csXyzFR5csXyz */
void csXyz::operator+=(csXyz& param_0) {
    x += param_0.x;
    y += param_0.y;
    z += param_0.z;
}

/* 80245F48-80245FEC       .text __ml__5csXyzFf */
csXyz csXyz::operator*(f32 param_0) {
    return csXyz(x * param_0, y * param_0, z * param_0);
}