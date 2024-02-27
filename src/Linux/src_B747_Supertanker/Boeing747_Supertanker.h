#ifndef __B747ST_H
#define __B747ST_H

#define STRICT 1
#include <cstdint>
#include "OrbiterAPI.h"
#include "Orbitersdk.h"
#include "VesselAPI.h"
#include "747STdefinitions.h"

//Vessel parameters
const double B747ST_SIZE = 22.8; //Mean radius in meters.

const double B747ST_EMPTYMASS = 178840; //Empty mass in kg.

const double B747ST_FUELMASS = 168260; //Fuel mass in kg.

const double B747ST_WATERMASS = 74200; //Water mass in kg.

const double B747ST_ISP = 2e4; //Fuel-specific impulse in m/s.

const double B747ST_WISP = 0.0625; //Specific impulse of water?. We are using this and WATERMASS to make a animation of water being discharged.

const double B747ST_MAXMAINTH = 500e3;  //Max main thrust in kN.

const double B747ST_MAXWATERTH = 100; //?

const double LANDING_GEAR_OPERATING_SPEED = 0.06;

const double ENGINE_ROTATION_SPEED = 25;

const VECTOR3 B747ST_CS = {496.48, 953.27, 135.78}; //Vessel's cross sections.

const VECTOR3 B747ST_PMI = {363.91, 396.64, 128.02}; //Principal moments of inertia.

const double B747ST_VLIFT_C = 7.65; //Chord lenght in meters;

const double B747ST_VLIFT_S = 511; //Wing area in m^2;

const double B747ST_VLIFT_A = 7.0; //Wing aspect ratio;

const double B747ST_HLIFT_C = 8.2; //Chord lenght in meters;

const double B747ST_HLIFT_S = 61.4473; //Wing area in m^2;

const double B747ST_HLIFT_A = 6.1156; //Wing aspect ratio;

const double B747ST_STAB_C = 3.59; //Stabilizer chord lenght in meters.

const double B747ST_STAB_S = 39.0753; //Stabilizer wing area in m^2.

const double B747ST_STAB_A = 2; //Stabilizer wing aspect ratio.

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

//B747ST class interface

class B747ST : public VESSEL4{

    public:
        enum LandingGearStatus{GEAR_DOWN, GEAR_UP, GEAR_DEPLOYING, GEAR_STOWING} landing_gear_status;

        B747ST(OBJHANDLE hVessel, int flightmodel);
        virtual ~B747ST();

        void DefineAnimations(void);
        void ActivateLandingGear(LandingGearStatus action);
        void SetGearDown(void);
        void UpdateLandingGearAnimation(double);
        double UpdateLvlEnginesContrail();

        void ParkingBrake();

        void DischargeWater();

        void LightsControl();
        void ActivateBeacons();

        void clbkSetClassCaps(FILEHANDLE cfg) override;
        void clbkLoadStateEx(FILEHANDLE scn, void *vs) override;
        void clbkSaveState(FILEHANDLE scn) override;
        void clbkPreStep(double, double, double) override;
        void clbkPostStep(double, double, double) override;
        int clbkConsumeBufferedKey(int, bool, char *) override;

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

        AIRFOILHANDLE lwing, rwing, lstabilizer, rstabilizer;
        CTRLSURFHANDLE hlaileron, hraileron;
        THRUSTER_HANDLE th_main[4], th_retro[4], wdisch[2];
        THGROUP_HANDLE thg_main, thg_retro, wdisch_main;
        MESHHANDLE B747ST_mesh;
        BEACONLIGHTSPEC beacon[5];
        LightEmitter *l1, *l2, *l3, *l4;

        COLOUR4 col_d = {0.9,0.8,1,0};
	    COLOUR4 col_s = {1.9,0.8,1,0};
	    COLOUR4 col_a = {0,0,0,0};
};

#endif //!__B747ST_H