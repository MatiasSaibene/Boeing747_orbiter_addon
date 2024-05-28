#pragma once

#ifndef __BOEING747SOFIA_H
#define __BOEING747SOFIA_H

#define STRICT 1
#include <cstdint>
#include "OrbiterAPI.h"
#include "Orbitersdk.h"
#include "VesselAPI.h"
#include "747SOFIAdefinitions.h"
#include "747cockpitdefinitions.h"
#include "XRSound.h"


//Vessel parameters
const double B747SOFIA_SIZE = 25.0;  //Mean radius in meters.

const double B747SOFIA_EMPTYMASS = 147540; //Empty mass in kg.

const double B747SOFIA_FUELMASS = 190630; //Fuel mass in kg.

const double B747SOFIA_ISP = 32373; //Fuel-specific impulse in m/s.

const double B747SOFIA_MAXMAINTH = 400e3; //Max main thrust in kN.

const double LANDING_GEAR_OPERATING_SPEED = 0.06;

const double ENGINE_ROTATION_SPEED = 10;

const VECTOR3 B747SOFIA_CS = {401.28, 868.57, 134.25};

const VECTOR3 B747SOFIA_PMI = {204.50, 244.01, 135.71};

const double B747SOFIA_VLIFT_C = 7.65; //Chord lenght in meters;

const double B747SOFIA_VLIFT_S = 511; //Wing area in m^2;

const double B747SOFIA_VLIFT_A = 7.0; //Wing aspect ratio;

const double B747SOFIA_HLIFT_C = 8.2; //Chord lenght in meters;

const double B747SOFIA_HLIFT_S = 61.4473; //Wing area in m^2;

const double B747SOFIA_HLIFT_A = 6.1156; //Wing aspect ratio;

const double B747SOFIA_STAB_C = 3.59; //Stabilizer chord lenght in meters.

const double B747SOFIA_STAB_S = 39.0753; //Stabilizer wing area in m^2.

const double B747SOFIA_STAB_A = 2; //Stabilizer wing aspect ratio.

const VECTOR3 B747SOFIA_COCKPIT_OFFSET = Cockpit_offset_Location;

const VECTOR3 MFD_BUTTON_POS[12] = {
    {MFD1_BTN1_Location},
    {MFD1_BTN2_Location},
    {MFD1_BTN3_Location},
    {MFD1_BTN4_Location},
    {MFD1_BTN5_Location},
    {MFD1_BTN6_Location},
    {MFD1_BTN7_Location},
    {MFD1_BTN8_Location},
    {MFD1_BTN9_Location},
    {MFD1_BTN10_Location},
    {MFD1_BTN11_Location},
    {MFD1_BTN12_Location},
};

const VECTOR3 MFD_CTRL_POS[3] = {
    {MFD1_PWR_Location},
    {MFD1_SEL_Location},
    {MFD1_MNU_Location}
};

//Define touchdown points
//For gear down
static const int ntdvtx_geardown = 14;
static TOUCHDOWNVTX tdvtx_geardown[ntdvtx_geardown] = {
    {(TDP1_Location), 5e6, 5e5, 1.6, 0.1},
    {(TDP2_Location), 5e6, 5e5, 3.0, 0.2},
    {(TDP3_Location), 5e6, 5e5, 3.0, 0.2},
    {(TDP4_Location), 5e6, 5e6, 3.0},
    {(TDP5_Location), 5e6, 5e6, 3.0},
    {(TDP6_Location), 5e6, 5e6, 3.0},
    {(TDP7_Location), 5e6, 5e6, 3.0},
    {(TDP8_Location), 5e6, 5e6, 3.0},
    {(TDP9_Location), 5e6, 5e6, 3.0},
    {(TDP10_Location), 5e6, 5e6, 3.0},
    {(TDP11_Location), 5e6, 5e6, 3.0},
    {(TDP12_Location), 5e6, 5e6, 3.0},
    {(TDP13_Location), 5e6, 5e6, 3.0},
    {(TDP14_Location), 5e6, 5e6, 3.0},
};


//For gear up
static const int ntdvtx_gearup = 11;
static TOUCHDOWNVTX tdvtx_gearup[ntdvtx_gearup] = {
    {(TDP4_Location), 5e6, 5e6, 3.0},
    {(TDP5_Location), 5e6, 5e6, 3.0},
    {(TDP6_Location), 5e6, 5e6, 3.0},
    {(TDP7_Location), 5e6, 5e6, 3.0},
    {(TDP8_Location), 5e6, 5e6, 3.0},
    {(TDP9_Location), 5e6, 5e6, 3.0},
    {(TDP10_Location), 5e6, 5e6, 3.0},
    {(TDP11_Location), 5e6, 5e6, 3.0},
    {(TDP12_Location), 5e6, 5e6, 3.0},
    {(TDP13_Location), 5e6, 5e6, 3.0},
    {(TDP14_Location), 5e6, 5e6, 3.0},
};

//B747SOFIA class interface


class B747SOFIA : public VESSEL4{

    public:
        
        enum MySounds {engines_start, engines_shutdown, engines, cabin_ambiance, rotate, gear_movement};
        
        enum LandingGearStatus{GEAR_DOWN, GEAR_UP, GEAR_DEPLOYING, GEAR_STOWING} landing_gear_status;

        enum TelescopeHatchStatus{HATCH_CLOSED, HATCH_OPEN, HATCH_OPENING, HATCH_CLOSING} telescope_hatch_status;

        B747SOFIA(OBJHANDLE hVessel, int flightmodel);
        virtual ~B747SOFIA();
        
        void DefineAnimations(void);

        void ActivateLandingGear(LandingGearStatus action);
        void SetGearDown(void);
        void UpdateGearStatus(void);

        void UpdateLandingGearAnimation(double);
        void ActivateTelescopeHatch(TelescopeHatchStatus telescope_hatch_status);
        void OpenTelescopeHatch(void);
        void UpdateTelescopeHatchAnimation(double);

        double UpdateLvlEnginesContrail();

        void ParkingBrake();

        void ActivateBeacons(void);

        void LightsControl(void);

        void EnginesAutostart(void);
        void EnginesAutostop(void);
        void UpdateEnginesStatus(void);

        void clbkSetClassCaps(FILEHANDLE cfg) override;
        void clbkLoadStateEx(FILEHANDLE scn, void *vs) override;
        void clbkSaveState(FILEHANDLE scn) override;
        void clbkPreStep(double, double, double) override;
        void clbkPostCreation(void) override;
        void clbkPostStep(double, double, double) override;
        int clbkConsumeBufferedKey(int, bool, char *) override;

        bool clbkLoadVC(int) override;

        MESHHANDLE B747SOFIA_mesh, mhcockpit_mesh;  //Mesh handle
        unsigned int uimesh_Cockpit = 1;

        XRSound *m_pXRSound;


    private:

        unsigned int anim_landing_gear;
        unsigned int anim_door;
        unsigned int anim_laileron;
        unsigned int anim_raileron;
        unsigned int anim_elevator;
        unsigned int anim_elevator_trim;
        unsigned int anim_rudder;
        unsigned int anim_engines;
        unsigned int anim_telescope_hatch;

        double lvlcontrailengines;
        double landing_gear_proc;
        double engines_proc;
        double telescope_hatch_proc;
        double pwr;

        AIRFOILHANDLE lwing, rwing, lstabilizer, rstabilizer;
        CTRLSURFHANDLE hlaileron, hraileron;
        THRUSTER_HANDLE th_main[4], th_retro[4];
        THGROUP_HANDLE thg_main, thg_retro;
        BEACONLIGHTSPEC beacongreen[2], beaconred[2], beaconwhite[1];
        LightEmitter *l1, *l2, *l3, *l4, *cpl1, *cpl2;
        

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

#endif