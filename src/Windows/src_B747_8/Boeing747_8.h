#pragma once

#ifndef __BOEING747_8_H
#define __BOEING747_8_H

#define STRICT 1
#include <cstdint>
#include "OrbiterAPI.h"
#include "Orbitersdk.h"
#include "VesselAPI.h"
#include "7478definitions.h"
#include "747cockpitdefinitions.h"
#include "747FCdefinitions.h"
#include "XRSound.h"

//Vessel parameters
const double B7478_SIZE = 25; //Mean radius in meters.

const double B7478_EMPTYMASS = 190962; //Empty mass in kg.

const double B7478_FUELMASS = 256734; //Fuel mass in kg.

const double B7478_ISP = 2e4; //Fuel-specific impulse in m/s.

const double B7478_MAXMAINTH = 750e3;  //Max main thrust in kN.

const double LANDING_GEAR_OPERATING_SPEED = 0.06;

const double ENGINE_ROTATION_SPEED = 25;

const VECTOR3 B7478_CS = {536.48, 983.15, 135.15}; //Vessel's cross sections.

const VECTOR3 B7478_PMI = {335.85, 364.66, 125.38}; //Principal moments of inertia.

const double B7478_VLIFT_C = 7.65; //Chord lenght in meters;

const double B7478_VLIFT_S = 511; //Wing area in m^2;

const double B7478_VLIFT_A = 7.0; //Wing aspect ratio;

const double B7478_HLIFT_C = 8.2; //Chord lenght in meters;

const double B7478_HLIFT_S = 61.4473; //Wing area in m^2;

const double B7478_HLIFT_A = 6.1156; //Wing aspect ratio;

const double B7478_STAB_C = 3.59; //Stabilizer chord lenght in meters.

const double B7478_STAB_S = 39.0753; //Stabilizer wing area in m^2.

const double B7478_STAB_A = 2; //Stabilizer wing aspect ratio.

const VECTOR3 B7478_COCKPIT_OFFSET = Cockpit_offset_Location;

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

//B7478 class interface

class B7478 : public VESSEL4{

    public:

        enum MySounds {engines_start, engines_shutdown, engines, cabin_ambiance, rotate, gear_movement};
        
        enum LandingGearStatus{GEAR_DOWN, GEAR_UP, GEAR_DEPLOYING, GEAR_STOWING} landing_gear_status;

        B7478(OBJHANDLE hVessel, int flightmodel);
        virtual ~B7478();

        void DefineAnimations(void);
        void ActivateLandingGear(LandingGearStatus action);
        void SetGearDown(void);
        void UpdateLandingGearAnimation(double);
        void UpdateGearStatus(void);

        double UpdateLvlEnginesContrail();

        void ParkingBrake();

        void NextSkin();
        void ChangeLivery();
        void ApplyLivery();

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
        virtual int clbkConsumeBufferedKey(DWORD, bool, char *) override;

        bool clbkLoadVC(int) override;


        void clbkVisualCreated(VISHANDLE vis, int refcount) override;
        void clbkVisualDestroyed (VISHANDLE vis, int refcount) override;

        VISHANDLE visual;
        MESHHANDLE b7478_mesh, mhcockpit_mesh, fccabin_mesh;  //Mesh handle
        unsigned int uimesh_Cockpit = 1;
        DEVMESHHANDLE b7478_dmesh;  //Mesh template handle

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

        double lvlcontrailengines;
        double landing_gear_proc;
        double engines_proc;
        double pwr;

        AIRFOILHANDLE lwing, rwing, lstabilizer, rstabilizer;
        CTRLSURFHANDLE hlaileron, hraileron;
        THRUSTER_HANDLE th_main[4], th_retro[4];
        THGROUP_HANDLE thg_main, thg_retro;
        BEACONLIGHTSPEC beacon[5];
        FILEHANDLE skinlist, skinlog;
        SURFHANDLE skin[5];
        SURFHANDLE vcMfdTex;
        char skinpath[256];
        LightEmitter *l1, *l2, *l3, *l4, *cpl1, *cpl2, *fcl1, *fcl2, *fcl3, *fcl4, *fcl5, *fcl6, *fcl7, *fcl8, *fcl9, *fcl10, *fcl11, *fcl12;
        

        COLOUR4 col_d = {0.9,0.8,1,0};
	    COLOUR4 col_s = {1.9,0.8,1,0};
	    COLOUR4 col_a = {0,0,0,0};
        COLOUR4 ccol_d = {1, 0.508, 0.100};
        COLOUR4 ccol_s = {1, 0.508, 0.100};
        COLOUR4 ccol_a = {1, 0.508, 0.100};
        COLOUR4 fccol_d = {1, 1, 1};
        COLOUR4 fccol_s = {1, 1, 1};
        COLOUR4 fccol_a = {1, 1, 1};

        const char fname[18] = "B7478_skins.txt";  //File where skin list is stored. Relative to ORBITER_ROOT.
        const char skindir[27] = "Boeing_747\\B747_8\\Skins\\";  //Path where actual skins are stored. Relative to ORBITER_ROOT\\Textures.
        char skinname[256];

        //Name of the textures to be applied.
        const char texname_fus[14] = "\\Fuselage.dds";
        const char texname_vs[25] = "\\Vertical_stabilizer.dds";
        const char texname_rw[16] = "\\Right_wing.dds";
        const char texname_lw[15] = "\\Left_wing.dds";
        const char texname_eng[10] = "\\ENG1.dds";
};

#endif //!__BOEING7478_H