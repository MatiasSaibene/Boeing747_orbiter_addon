#pragma once

#ifndef __BOEING747_YAL1_H
#define __BOEING747_YAL1_H

#define STRICT 1
#include <cstdint>
#include "OrbiterAPI.h"
#include "Orbitersdk.h"
#include "VesselAPI.h"
#include "B985121definitions.h"
#include "XRSound.h"

//Vessel parameters
const double B985121_SIZE = 6; //Mean radius in meters.

const double B985121_EMPTYMASS = 12000; //Empty mass in kg.

const double B985121_FUELMASS = 1000; //Fuel mass in kg.

const double B985121_ISP = 25e4; //Fuel-specific impulse in m/s.

const double B985121_MAXMAINTH = 12.5e4;  //Max main thrust in kN.

//const double LANDING_GEAR_OPERATING_SPEED = 0.06;

const VECTOR3 B985121_CS = {9.44, 24.94, 2.38}; //Vessel's cross sections.

const VECTOR3 B985121_PMI = {3.78, 4.64, 2.38}; //Principal moments of inertia.

const double B985121_VLIFT_C = 5.255; //Chord lenght in meters;

const double B985121_VLIFT_S = 17.5378; //Wing area in m^2;

const double B985121_VLIFT_A = 1.97; //Wing aspect ratio;

const double B985121_HLIFT_C = 1.38; //Chord lenght in meters;

const double B985121_HLIFT_S = 1.5104; //Wing area in m^2;

const double B985121_HLIFT_A = 1.9359; //Wing aspect ratio;


const VECTOR3 B985121_COCKPIT_OFFSET = Cockpit_offset_Location;

//Define touchdown points

//For gear up
static const int ntdvtx_gearup = 7;
static TOUCHDOWNVTX tdvtx_gearup[ntdvtx_gearup] = {
    {(TDP2_Location), 1e6, 1e5, 1.6, 0.1},
    {(TDP3_Location), 1e6, 1e5, 1.6, 0.1},
    {(TDP4_Location), 1e6, 1e5, 1.6, 0.1},
    {(TDP1_Location), 2e4, 1e3, 3.0},
    {(TDP5_Location), 2e4, 1e3, 3.0},
    {(TDP6_Location), 2e4, 1e3, 3.0},
    {(TDP7_Location), 2e4, 1e3, 3.0},
};

//B985121 class interface

class B985121 : public VESSEL4{

    public:

        B985121(OBJHANDLE hVessel, int flightmodel);
        virtual ~B985121();

        void DefineAnimations(void);

        double UpdateParticleLvl();

        void ActivateBeacons(void);

        void LightsControl(void);


        void clbkSetClassCaps(FILEHANDLE cfg) override;
        void clbkPostStep(double, double, double) override;
        int clbkConsumeBufferedKey(int, bool, char *) override;


        MESHHANDLE B985121_mesh;  //Mesh handle

        XRSound *m_pXRSound;

    private:

        unsigned int anim_laileron;
        unsigned int anim_raileron;
        unsigned int anim_elevator;
        unsigned int anim_elevator_trim;
        unsigned int anim_rudder;

        PARTICLESTREAMSPEC soundbarrierpart;
		double lvl;

        AIRFOILHANDLE hwing, lstabilizer, rstabilizer;
        CTRLSURFHANDLE hlaileron, hraileron;
        THRUSTER_HANDLE th_main;
        THGROUP_HANDLE thg_main;
        BEACONLIGHTSPEC beacon[5];
        SURFHANDLE exhaust_tex;
        LightEmitter *l1, *l2;
        DOCKHANDLE dock;
        

        COLOUR4 col_d = {0.9,0.8,1,0};
	    COLOUR4 col_s = {1.9,0.8,1,0};
	    COLOUR4 col_a = {0,0,0,0};
        COLOUR4 ccol_d = {1, 0.508, 0.100};
        COLOUR4 ccol_s = {1, 0.508, 0.100};
        COLOUR4 ccol_a = {1, 0.508, 0.100};
        COLOUR4 fccol_d = {1, 1, 1};
        COLOUR4 fccol_s = {1, 1, 1};
        COLOUR4 fccol_a = {1, 1, 1};
};

#endif //!__BOEING985_121_H