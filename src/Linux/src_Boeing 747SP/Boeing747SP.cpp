//Copyright (c) Matías Saibene
//Licenced under the MIT Licence

//==========================================
//          ORBITER MODULE: Boeing 747SP
//
//Boeing747SP.cpp
//Control module for Boeing 747SP vessel class
//
//==========================================

#define ORBITER_MODULE
#include "Boeing747SP.h"
#include <cstring>
#include <cstdio>
#include <algorithm>


bool parkingBrakeEnabled;
bool lights_on;
static int currentSkin = 0;

// 1. vertical lift component

void VLiftCoeff (VESSEL *v, double aoa, double M, double Re, void *context, double *cl, double *cm, double *cd)
{
	const int nabsc = 9;
	static const double AOA[nabsc] = {-180*RAD,-60*RAD,-30*RAD, -15*RAD, 0*RAD,15*RAD,30*RAD,60*RAD,180*RAD};
	static const double CL[nabsc]  = {   0,    -0.56,   -0.56,   -0.16,  0.15,  0.46,  0.56,  0.56,  0.00};
	static const double CM[nabsc]  = {    0,    0.00,   0.00,     0.00,  0.00,  0.00,  0.00,  0.00,  0.00};


	int i;
	for (i = 0; i < nabsc-1 && AOA[i+1] < aoa; i++);
	if (i < nabsc - 1) {
		double f = (aoa - AOA[i]) / (AOA[i + 1] - AOA[i]);
		*cl = CL[i] + (CL[i + 1] - CL[i]) * f;  // aoa-dependent lift coefficient
		*cm = CM[i] + (CM[i + 1] - CM[i]) * f;  // aoa-dependent moment coefficient
	}
	else {
		*cl = CL[nabsc - 1];
		*cm = CM[nabsc - 1];
	}
	double saoa = sin(aoa);
	double pd = 0.015 + 0.4*saoa*saoa;  // profile drag
	*cd = pd + oapiGetInducedDrag (*cl, B747SP_VLIFT_A, 0.7) + oapiGetWaveDrag (M, 0.75, 1.0, 1.1, 0.04);
	// profile drag + (lift-)induced drag + transonic/supersonic wave (compressibility) drag
}

// 2. horizontal lift component (vertical stabilisers and body)

void HLiftCoeff (VESSEL *v, double beta, double M, double Re, void *context, double *cl, double *cm, double *cd)
{
	int i;
	const int nabsc = 8;
	static const double BETA[nabsc] = {-180*RAD,-135*RAD,-90*RAD,-45*RAD,45*RAD,90*RAD,135*RAD,180*RAD};
	static const double CL[nabsc]   = {       0,    +0.3,      0,   -0.3,  +0.3,     0,   -0.3,      0};
	for (i = 0; i < nabsc-1 && BETA[i+1] < beta; i++);
	if (i < nabsc - 1) {
		*cl = CL[i] + (CL[i + 1] - CL[i]) * (beta - BETA[i]) / (BETA[i + 1] - BETA[i]);
	}
	else {
		*cl = CL[nabsc - 1];
	}
	*cm = 0.0;
	*cd = 0.015 + oapiGetInducedDrag (*cl, B747SP_HLIFT_A, 0.6) + oapiGetWaveDrag (M, 0.75, 1.0, 1.1, 0.04);
}

//Constructor
B747SP::B747SP(OBJHANDLE hVessel, int flightmodel) : VESSEL4(hVessel, flightmodel){

    landing_gear_proc = 0.0;

	landing_gear_status = GEAR_DOWN;

	DefineAnimations();

    b747sp_mesh = NULL;

    mhcockpit_mesh = NULL;

    skinpath[0] = '\0';
    for (int i = 0; i < 5; i++)
        skin[i] = 0;

}

//Destructor
B747SP::~B747SP(){

    /*oapiDeleteMesh(b747sp_mesh);

    for(int i = 0; i < 5; i++)
        if(skin[i]) oapiReleaseTexture(skin[i]);

    for(int i = 0; i < 5; i++)
        if(skin[i]) oapiDestroySurface(skin[i]);
*/
}

void B747SP::DefineAnimations(void){
    
    //Front landing gear

    static unsigned int FrontLandingGearGrp[1] = {Front_landing_gear_Id};
    static MGROUP_ROTATE FrontLandingGearRotate(
        0,
        FrontLandingGearGrp,
        1,
        (Axis_front_landing_gear_rotate_Location),
        _V(1, 0, 0),
        (float)(-110*RAD)
    );

    static unsigned int FrontLandingGearLeftDoorGrp[1] = {Front_landing_gear_left_door_Id};
    static MGROUP_ROTATE FrontLandingGearLeftDoor(
        0,
        FrontLandingGearLeftDoorGrp,
        1,
        (Axis_front_landing_gear_left_door_Location),
        _V(0, 0, 1),
        (float)(90*RAD)
    );

    static unsigned int FrontLandingGearRightDoorGrp[1] = {Front_landing_gear_right_door_Id};
    static MGROUP_ROTATE FrontLandingGearRightDoor(
        0,
        FrontLandingGearRightDoorGrp,
        1,
        (Axis_front_landing_gear_right_door_Location),
        _V(0, 0, 1),
        (float)(-90*RAD)
    );

    anim_landing_gear = CreateAnimation(0.0);

    AddAnimationComponent(anim_landing_gear, 0, 0.5, &FrontLandingGearRotate);
    AddAnimationComponent(anim_landing_gear, 0, 0.5, &FrontLandingGearLeftDoor);
    AddAnimationComponent(anim_landing_gear, 0, 0.5, &FrontLandingGearRightDoor);

    //Rear landing gears

    static unsigned int RearLeftWingLandingGearGrp[1] = {Rear_left_wing_landing_gear_Id};
    static MGROUP_ROTATE RearLeftWingLandingGearStow(
        0,
        RearLeftWingLandingGearGrp,
        1,
        (Axis_left_wing_landing_gear_Location),
        _V(0, 0, 1),
        (float)(90*RAD)
    );
    
    static unsigned int RearLeftWingLandingGearPartGrp [1] = {Rear_left_wing_landing_gear_part_Id};
    static MGROUP_ROTATE RearLeftWingLandingGearPart(
        0,
        RearLeftWingLandingGearPartGrp,
        1,
        (Axis_rear_left_wing_landing_gear_part_Location),
        _V(0, 0, 1),
        (float)(-90*RAD)
    );

    AddAnimationComponent(anim_landing_gear, 0, 0.5, &RearLeftWingLandingGearStow);
    AddAnimationComponent(anim_landing_gear, 0, 0.5, &RearLeftWingLandingGearPart);

    static unsigned int RearRightWingLandingGearGrp[1] = {Rear_right_wing_landing_gear_Id};
    static MGROUP_ROTATE RearRightWingLandingGearStow(
        0,
        RearRightWingLandingGearGrp,
        1,
        (Axis_right_wing_landing_gear_Location),
        _V(0, 0, 1),
        (float)(-90*RAD)
    );

    static unsigned int RearRightWingLandingGearPartGrp[1] = {Rear_right_wing_landing_gear_part_Id};
    static MGROUP_ROTATE RearRightWingLandingGearPart(
        0,
        RearRightWingLandingGearPartGrp,
        1,
        (Axis_rear_right_wing_landing_gear_part_Location),
        _V(0, 0, 1),
        (float)(90*RAD)
    );

    AddAnimationComponent(anim_landing_gear, 0, 0.5, &RearRightWingLandingGearStow);
    AddAnimationComponent(anim_landing_gear, 0, 0.5, &RearRightWingLandingGearPart);

    static unsigned int RearLeftLandingGearGrp[1] = {Rear_left_landing_gear_Id};
    static MGROUP_ROTATE RearLeftLandingGear(
        0,
        RearLeftLandingGearGrp,
        1,
        (Axis_left_landing_gear_Location),
        _V(1, 0, 0),
        (float)(-180*RAD)
    );

    static unsigned int RearRightLandingGearGrp[1] = {Rear_right_landing_gear_Id};
    static MGROUP_ROTATE RearRightLandingGear(
        0,
        RearRightLandingGearGrp,
        1,
        (Axis_right_landing_gear_Location),
        _V(1, 0, 0),
        (float)(-180*RAD)
    );

    AddAnimationComponent(anim_landing_gear, 0, 0.5, &RearLeftLandingGear);
    AddAnimationComponent(anim_landing_gear, 0, 0.5, &RearRightLandingGear);

    static unsigned int RearLeftLandingGearDoor1Grp[2] = {Rear_left_landing_gear_door1_Id, Rear_left_landing_gear_door2_Id};
    static MGROUP_ROTATE RearLeftLandingGearDoor1(
        0,
        RearLeftLandingGearDoor1Grp,
        2,
        (Axis_landing_gear_left_door_1_Location),
        _V(0, 0, 1),
        (float)(-90*RAD)
    );

    static unsigned int RearLeftLandingGearDoor2Grp[1] = {Rear_left_landing_gear_door2_Id};
    static MGROUP_ROTATE RearLeftLandingGearDoor2(
        0,
        RearLeftLandingGearDoor2Grp,
        1,
        (Axis_left_landing_gear_door2_Location),
        _V(0, 0, 1),
        (float)(-180*RAD)
    );

    AddAnimationComponent(anim_landing_gear, 0.25, 0.5, &RearLeftLandingGearDoor1);
    AddAnimationComponent(anim_landing_gear, 0.5, 0.75, &RearLeftLandingGearDoor2);

    static unsigned int RearRightLandingGearDoor1Grp[2] = {Rear_right_landing_gear_door1_Id, Rear_right_landing_gear_door2_Id};
    static MGROUP_ROTATE RearRightLandingGearDoor1(
        0,
        RearRightLandingGearDoor1Grp,
        2,
        (Axis_landing_gear_right_door_1_Location),
        _V(0, 0, 1),
        (float)(90*RAD)
    );

    static unsigned int RearRightLandingGearDoor2Grp[1] = {Rear_right_landing_gear_door2_Id};
    static MGROUP_ROTATE RearRightLandingGearDoor2(
        0,
        RearRightLandingGearDoor2Grp,
        1,
        (Axis_right_landing_gear_door2_Location),
        _V(0, 0, 1),
        (float)(180*RAD)
    );

    AddAnimationComponent(anim_landing_gear, 0.25, 0.5, &RearRightLandingGearDoor1);
    AddAnimationComponent(anim_landing_gear, 0.5, 0.75, &RearRightLandingGearDoor2);

    //Engines

    static unsigned int Engine1Grp[1] = {ENG1_blades_Id};
    static MGROUP_ROTATE Engine1(
        0,
        Engine1Grp,
        1,
        (ENG1_blades_Location),
        _V(0, 0, 1),
        (float)(360*RAD)
    );
    
    
    static unsigned int Engine2Grp[1] = {ENG2_blades_Id};
    static MGROUP_ROTATE Engine2(
        0,
        Engine2Grp,
        1,
        (ENG2_blades_Location),
        _V(0, 0, 1),
        (float)(360*RAD)
    );

    static unsigned int Engine3Grp[1] = {ENG3_blades_Id};
    static MGROUP_ROTATE Engine3(
        0,
        Engine3Grp,
        1,
        (ENG3_blades_Location),
        _V(0, 0, 1),
        (float)(360*RAD)
    );

    static unsigned int Engine4Grp[1] = {ENG4_blades_Id};
    static MGROUP_ROTATE Engine4(
        0,
        Engine4Grp,
        1,
        (ENG4_blades_Location),
        _V(0, 0, 1),
        (float)(360*RAD)
    );
    
    anim_engines = CreateAnimation(0.0);

    AddAnimationComponent(anim_engines, 0, 1, &Engine1);
    AddAnimationComponent(anim_engines, 0, 1, &Engine2);
    AddAnimationComponent(anim_engines, 0, 1, &Engine3);
    AddAnimationComponent(anim_engines, 0, 1, &Engine4);

    //Control surfaces

    static unsigned int LeftElevatorGrp[1] = {Left_elevator_trim_Id};
    static MGROUP_ROTATE LeftElevator(
        0,
        LeftElevatorGrp,
        1,
        (Axis_elevator_left_Location),
        _V(1, 0, 0.5),
        (float)(45*RAD)
    );

    static unsigned int RightElevatorGrp[1] = {Right_elevator_trim_Id};
    static MGROUP_ROTATE RightElevator(
        0,
        RightElevatorGrp,
        1,
        (Axis_elevator_right_Location),
        _V(1, 0, -0.5),
        (float)(45*RAD)
    );

    anim_elevator = CreateAnimation(0.5);
    AddAnimationComponent(anim_elevator, 0, 1, &LeftElevator);
    AddAnimationComponent(anim_elevator, 0, 1, &RightElevator);

    static unsigned int LeftElevatorTrimGrp[1] = {Left_elevator_trim_Id};
    static MGROUP_ROTATE LeftElevatorTrim(
        0,
        LeftElevatorTrimGrp,
        1,
        (Axis_elevator_left_Location),
        _V(1, 0, 0.5),
        (float)(22.5*RAD)
    );

    static unsigned int RightElevatorTrimGrp[1] = {Right_elevator_trim_Id};
    static MGROUP_ROTATE RightElevatorTrim(
        0,
        RightElevatorTrimGrp,
        1,
        (Axis_elevator_right_Location),
        _V(1, 0, -0.5),
        (float)(22.5*RAD)
    );

    anim_elevator_trim = CreateAnimation(0.5);
    AddAnimationComponent(anim_elevator_trim, 0, 1, &LeftElevatorTrim);
    AddAnimationComponent(anim_elevator_trim, 0, 1, &RightElevatorTrim);

    static unsigned int RudderGrp[1] = {Rudder_Id};
    static MGROUP_ROTATE Rudder(
        0,
        RudderGrp,
        1,
        (Axis_rudder_Location),
        _V(0, 1, 0),
        (float)(22.5*RAD)
    );
    anim_rudder = CreateAnimation(0.5);
    AddAnimationComponent(anim_rudder, 0, 1, &Rudder);

    static unsigned int LAileronGrp[1] = {LAileron_Id};
    static MGROUP_ROTATE LAileron(
        0,
        LAileronGrp,
        1,
        (Axis_laileron_Location),
        _V(0.25, 0, 0),
        (float)(45*RAD)
    );

    static unsigned int RAileronGrp[1] = {Raileron_Id};
    static MGROUP_ROTATE RAileron(
        0,
        RAileronGrp,
        1,
        (Axis_raileron_Location),
        _V(0.25, 0, 0),
        (float)(45*RAD)
    );

    anim_laileron = CreateAnimation(0.5);
    anim_raileron = CreateAnimation(0.5);

    AddAnimationComponent(anim_laileron, 0, 1, &LAileron);
    AddAnimationComponent(anim_raileron, 0, 1, &RAileron);


    //Cockpit

    static unsigned int LYokeColumnGrp[2] = {LYoke_column_Id, LYoke_Id};
    static MGROUP_ROTATE LYokeColumn(
        uimesh_Cockpit,
        LYokeColumnGrp,
        2,
        (Axis_LYoke_column_Location),
        _V(-1, 0, 0),
        (float)(30*RAD)
    );

    static unsigned int RYokeColumnGrp[2] = {RYoke_column_Id, RYoke_Id};
    static MGROUP_ROTATE RYokeColumn(
        uimesh_Cockpit,
        RYokeColumnGrp,
        2,
        (Axis_RYoke_column_Location),
        _V(-1, 0, 0),
        (float)(30*RAD)
    );

    AddAnimationComponent(anim_elevator, 0, 1, &LYokeColumn);
    AddAnimationComponent(anim_elevator, 0, 1, &RYokeColumn);

    static unsigned int LYokeGrp[1] = {LYoke_Id};
    static MGROUP_ROTATE LYoke(
        uimesh_Cockpit,
        LYokeGrp,
        1,
        (LYoke_Location),
        _V(0, 0, -1),
        (float)(90*RAD)
    );

    static unsigned int RYokeGrp[1] = {RYoke_Id};
    static MGROUP_ROTATE RYoke(
        uimesh_Cockpit,
        RYokeGrp,
        1,
        (RYoke_Location),
        _V(0, 0, -1),
        (float)(90*RAD)
    );

    AddAnimationComponent(anim_laileron, 0, 1, &LYoke);
    AddAnimationComponent(anim_laileron, 0, 1, &RYoke);

}

void B747SP::clbkSetClassCaps(FILEHANDLE cfg){

    //Physical vessel parameters
    SetSize(B747SP_SIZE);
    SetEmptyMass(B747SP_EMPTYMASS);
    SetCrossSections(B747SP_CS);
    SetPMI(B747SP_PMI);
    SetMaxWheelbrakeForce(89e3);
    SetRotDrag(_V(10, 10, 2.5));

    PROPELLANT_HANDLE JET_A1 = CreatePropellantResource(B747SP_FUELMASS);

	th_main[0] = CreateThruster((ENG1_Location), _V(0, 0, 1), B747SP_MAXMAINTH, JET_A1, B747SP_ISP);
    th_main[1] = CreateThruster((ENG2_Location), _V(0, 0, 1), B747SP_MAXMAINTH, JET_A1, B747SP_ISP);
    th_main[2] = CreateThruster((ENG3_Location), _V(0, 0, 1), B747SP_MAXMAINTH, JET_A1, B747SP_ISP);
    th_main[3] = CreateThruster((ENG4_Location), _V(0, 0, 1), B747SP_MAXMAINTH, JET_A1, B747SP_ISP);
    thg_main = CreateThrusterGroup(th_main, 4, THGROUP_MAIN);

    th_retro[0] = CreateThruster((ENG1_Location), _V(0, 0, -1), (B747SP_MAXMAINTH/4), JET_A1, B747SP_ISP);
    th_retro[1] = CreateThruster((ENG2_Location), _V(0, 0, -1), (B747SP_MAXMAINTH/4), JET_A1, B747SP_ISP);
    th_retro[2] = CreateThruster((ENG3_Location), _V(0, 0, -1), (B747SP_MAXMAINTH/4), JET_A1, B747SP_ISP);
    th_retro[3] = CreateThruster((ENG4_Location), _V(0, 0, -1), (B747SP_MAXMAINTH/4), JET_A1, B747SP_ISP);
    thg_retro = CreateThrusterGroup(th_retro, 4, THGROUP_RETRO);

	//Contrail effect on engines
    static PARTICLESTREAMSPEC engines_contrails = {
        0, 0.5, .95, 120, 0.03, 10.0, 5, 3.0, 
        PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_PLIN, -1.0, 25.0,
		PARTICLESTREAMSPEC::ATM_PLIN, 
    };
	AddParticleStream(&engines_contrails, (ENG1_Location), _V(0, 0, -1), &lvlcontrailengines);
    AddParticleStream(&engines_contrails, (ENG2_Location), _V(0, 0, -1), &lvlcontrailengines);
    AddParticleStream(&engines_contrails, (ENG3_Location), _V(0, 0, -1), &lvlcontrailengines);
    AddParticleStream(&engines_contrails, (ENG4_Location), _V(0, 0, -1), &lvlcontrailengines);

	lwing = CreateAirfoil3(LIFT_VERTICAL, (Left_wing_Location), VLiftCoeff, 0, B747SP_VLIFT_C, (B747SP_VLIFT_S*4), B747SP_VLIFT_A);

    rwing = CreateAirfoil3(LIFT_VERTICAL,(Right_wing_Location), VLiftCoeff, 0, B747SP_VLIFT_C,(B747SP_VLIFT_S*4), B747SP_VLIFT_A);

    lstabilizer = CreateAirfoil3(LIFT_VERTICAL, (Left_stabilizer_Location), VLiftCoeff, 0, B747SP_STAB_C, B747SP_STAB_S, B747SP_STAB_A);

    rstabilizer = CreateAirfoil3(LIFT_VERTICAL, (Right_stabilizer_Location), VLiftCoeff, 0, B747SP_STAB_C, B747SP_STAB_S, B747SP_STAB_A);
    
    CreateAirfoil3(LIFT_HORIZONTAL, (Rudder_Location), HLiftCoeff, 0, B747SP_HLIFT_C, B747SP_HLIFT_S, B747SP_HLIFT_A);

    hlaileron = CreateControlSurface3(AIRCTRL_AILERON,8.3696, 1.7, (LAileron_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_raileron);
    hraileron = CreateControlSurface3(AIRCTRL_AILERON, 8.3696, 1.7, (Raileron_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_laileron);

    CreateControlSurface3(AIRCTRL_ELEVATOR, (14.4997*2), 1.7, (Left_elevator_trim_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_elevator);
    CreateControlSurface3(AIRCTRL_ELEVATOR, (14.4997*2), 1.7, (Right_elevator_trim_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_elevator);

    CreateControlSurface3(AIRCTRL_ELEVATORTRIM, (14.4997*2), 1.7, (Left_elevator_trim_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_elevator_trim);
    CreateControlSurface3(AIRCTRL_ELEVATORTRIM, (14.4997*2), 1.7, (Right_elevator_trim_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_elevator_trim);

    CreateControlSurface3(AIRCTRL_RUDDER, 20.6937, 1.7, (Rudder_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_rudder);

    //Add the mesh
    SetMeshVisibilityMode (AddMesh (b747sp_mesh = oapiLoadMeshGlobal ("Boeing747\\Boeing_747SP")), MESHVIS_EXTERNAL);
    //AddMesh(b747sp_mesh);

    //Add the mesh for the cockpit
    SetMeshVisibilityMode(AddMesh(mhcockpit_mesh = oapiLoadMeshGlobal("Boeing747\\Boeing_747_cockpit")), MESHVIS_VC);

    //Define beacons

    static VECTOR3 beaconpos[5] = {{Beacon1_left_wing_Location}, {Beacon2_right_wing_Location}, {Beacon3_upper_deck_Location}, {Beacon4_belly_landing_gear_Location}, {Beacon5_APU_Location}};
    static VECTOR3 beaconcol = {0, 1, 0};

    for(int i = 0; i < 5; i++){
		beacon[i].shape = BEACONSHAPE_STAR;
		beacon[i].pos = beaconpos+i;
		beacon[i].col = &beaconcol;
		beacon[i].size = 1;
		beacon[i].falloff = 0.4;
		beacon[i].period = 1;
		beacon[i].duration = 0.1;
		beacon[i].tofs = 0.2;
		beacon[i].active = false;
		AddBeacon(beacon+i);
	}

}

void B747SP::clbkVisualCreated(VISHANDLE vis, int refcount){

    visual = vis;

    b747sp_dmesh = GetDevMesh(vis, 0);

    ApplyLivery();

}

void B747SP::clbkVisualDestroyed(VISHANDLE vis, int refcount){

    visual = NULL;
    b747sp_dmesh = NULL;

}

void B747SP::NextSkin() {
    if (currentSkin >= 5) {
        currentSkin = 0;
    }

    ChangeLivery();
    currentSkin++;
}

void B747SP::ChangeLivery() {
    const char item[5] = "SKIN";
    char skinname[256];
    char completedir_fus[256];
    char completedir_vs[256];
    char completedir_rw[256];
    char completedir_eng[256];
    char completedir_lw[256];
    const char SKINLIST[][6] = {"SKIN1", "SKIN2", "SKIN3", "SKIN4", "SKIN5"};
    
    skinlist = oapiOpenFile(fname, FILE_IN, ROOT);
    oapiReadItem_string(skinlist, SKINLIST[currentSkin], skinname);


    strcpy(completedir_fus, skindir);
    strcat(completedir_fus, skinname);
    strcat(completedir_fus, texname_fus);

    strcpy(completedir_vs, skindir);
    strcat(completedir_vs, skinname);
    strcat(completedir_vs, texname_vs);

    strcpy(completedir_rw, skindir);
    strcat(completedir_rw, skinname);
    strcat(completedir_rw, texname_rw);

    strcpy(completedir_eng, skindir);
    strcat(completedir_eng, skinname);
    strcat(completedir_eng, texname_eng);

    strcpy(completedir_lw, skindir);
    strcat(completedir_lw, skinname);
    strcat(completedir_lw, texname_lw);

    skin[0] = oapiLoadTexture(completedir_fus);
    skin[1] = oapiLoadTexture(completedir_vs);
    skin[2] = oapiLoadTexture(completedir_rw);
    skin[3] = oapiLoadTexture(completedir_eng);
    skin[4] = oapiLoadTexture(completedir_lw);


    ApplyLivery();
}

void B747SP::ApplyLivery(){

    if(!b747sp_dmesh) return;

    if(skin[0]) oapiSetTexture(b747sp_dmesh, 1, skin[0]);

    if(skin[1]) oapiSetTexture(b747sp_dmesh, 2, skin[1]);

    if(skin[2]) oapiSetTexture(b747sp_dmesh, 3, skin[2]);

    if(skin[3]) oapiSetTexture(b747sp_dmesh, 4, skin[3]);

    if(skin[4]) oapiSetTexture(b747sp_dmesh, 9, skin[4]);

}

void B747SP::ParkingBrake(){

    if(!parkingBrakeEnabled){
        SetWheelbrakeLevel(1, 0, true);
        parkingBrakeEnabled = true;
    } else {
        SetWheelbrakeLevel(0, 0, true);
        parkingBrakeEnabled = false;
    }

}


void B747SP::ActivateBeacons(){

    for(int i = 0; i < 5; i++){
		if(!beacon[i].active){
				beacon[i].active = true;
		} else {
				beacon[i].active = false;
		}
	}
}

void B747SP::LightsControl(void){

    if(!lights_on){
        l1 = AddSpotLight((LIGHT1_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);
        l2 = AddSpotLight((LIGHT2_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);
        l3 = AddSpotLight((LIGHT3_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);
        l4 = AddSpotLight((LIGHT4_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);
        cpl1 = AddPointLight((PL1_Location), 1, 0.1, 0, 0.1, ccol_d, ccol_s, ccol_a);
        cpl1->SetVisibility(LightEmitter::VIS_COCKPIT);
        cpl2 = AddPointLight((PL2_Location), 1, 0.1, 0, 0.1, ccol_d, ccol_s, ccol_a);
        cpl2->SetVisibility(LightEmitter::VIS_COCKPIT);
        lights_on = true;
    } else {
        DelLightEmitter(l1);
        DelLightEmitter(l2);
        DelLightEmitter(l3);
        DelLightEmitter(l4);
        DelLightEmitter(cpl1);
        DelLightEmitter(cpl2);
        lights_on = false;
    }
}

bool B747SP::clbkLoadVC(int id){

    switch(id){
        case 0 : SetCameraOffset((Camera_Location));
        SetCameraDefaultDirection(_V(0, 0, 1));
        SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
        break;
    }
    return true;
}

int B747SP::clbkConsumeBufferedKey(int key, bool down, char *kstate){

    if(key == OAPI_KEY_G && down){
        SetGearDown();
        return 1;
    }
    if(key == OAPI_KEY_NUMPADENTER && down){
        ParkingBrake();
        return 1;
    }
    if(key == OAPI_KEY_B && down){
        ActivateBeacons();
        return 1;
    }
    if(key == OAPI_KEY_F && down){
        LightsControl();
        return 1;
    }
    if(key == OAPI_KEY_V && down){
        NextSkin();
        return 1;
    }
    return 0;
}

//Load vessel status from scenario file
void B747SP::clbkLoadStateEx(FILEHANDLE scn, void *vs){
    
    char *line;

    while(oapiReadScenario_nextline(scn, line)){
        if(!strncasecmp(line, "GEAR", 4)){
            sscanf(line+4, "%d%lf", (int *)&landing_gear_status, &landing_gear_proc);
            SetAnimation(anim_landing_gear, landing_gear_proc);
        } else if(!strncasecmp(line, "SKIN", 4)){
            sscanf(line+4, "%s", skinpath);
            char fname[256];
            strcpy(fname, "Boeing_747\\B747SP\\Skins\\");
            strcat(fname, skinpath);
            int n = strlen(fname); fname[n++] = '\\';

            strcpy(fname+n, "Fuselage.dds"); skin[0] = oapiLoadTexture(fname);

            strcpy(fname+n, "Vertical_stabilizer.dds"); skin[1] = oapiLoadTexture(fname);

            strcpy(fname+n, "Right_wing.dds"); skin[2] = oapiLoadTexture(fname);

            strcpy(fname+n, "ENG1.dds"); skin[3] = oapiLoadTexture(fname);

            strcpy(fname+n, "Left_wing.dds"); skin[4] = oapiLoadTexture(fname);

        } else {
            ParseScenarioLineEx(line, vs);
        }
    }
}

void B747SP::clbkSaveState(FILEHANDLE scn){

    char cbuf[256];

    SaveDefaultState(scn);
    sprintf(cbuf, "%d %0.4f", landing_gear_status, landing_gear_proc);
    oapiWriteScenario_string(scn, "GEAR", cbuf);
    
    if (skinpath[0])
		oapiWriteScenario_string (scn, "SKIN", skinpath);
}

//////////Logic for animations
void B747SP::SetGearDown(void){
    ActivateLandingGear((landing_gear_status == GEAR_DOWN || landing_gear_status == GEAR_DEPLOYING) ?
        GEAR_STOWING : GEAR_DEPLOYING);
}

void B747SP::ActivateLandingGear(LandingGearStatus action){
    landing_gear_status = action;
}

void B747SP::UpdateLandingGearAnimation(double simdt) {
    if (landing_gear_status >= GEAR_DEPLOYING) {
        double da = simdt * LANDING_GEAR_OPERATING_SPEED;
        if (landing_gear_status == GEAR_DEPLOYING) {
            if (landing_gear_proc > 0.0) landing_gear_proc = std::max(0.0, landing_gear_proc - da);
            else landing_gear_status = GEAR_DOWN;
            SetTouchdownPoints(tdvtx_geardown, ntdvtx_geardown);
        } else {
            if (landing_gear_proc < 1.0) landing_gear_proc = std::min(1.0, landing_gear_proc + da);
            else landing_gear_status = GEAR_UP;
            SetTouchdownPoints(tdvtx_gearup, ntdvtx_gearup);
        }
        SetAnimation(anim_landing_gear, landing_gear_proc);
    }
}

double B747SP::UpdateLvlEnginesContrail(){
    double machnumber = GetMachNumber();
    double altitude = GetAltitude();

    if((machnumber > 0.5) && ((altitude > 10000) && (altitude < 15000))){
        return 1.0;
    } else {
        return 0.0;
    }

}

void B747SP::clbkPostStep(double simt, double simdt, double mjd){
    UpdateLandingGearAnimation(simdt);
    lvlcontrailengines = UpdateLvlEnginesContrail();
}

void B747SP::clbkPreStep(double simt, double simdt, double mjd){

    double grndspd = GetGroundspeed();
    double pwr = GetThrusterLevel(th_main);
    double prp = GetAnimation(anim_engines);
    double msimdt = simdt * ENGINE_ROTATION_SPEED;
    double da = msimdt * 0.1 + (pwr * 0.1);

    engines_proc = prp + da;

    if(prp < 1){
        SetAnimation(anim_engines, engines_proc);
    } else {
        SetAnimation(anim_engines, 0.0);
    }
}

////////////////////////

DLLCLBK void InitModule(MODULEHANDLE hModule){


}

DLLCLBK void ExitModule(MODULEHANDLE *hModule){

}



///////////////Vessel initialization

DLLCLBK VESSEL *ovcInit(OBJHANDLE hvessel, int flightmodel){
    
	return new B747SP(hvessel, flightmodel);

}

/////////////Vessel memory cleanup
DLLCLBK void ovcExit(VESSEL *vessel){
    
	if(vessel) delete(B747SP*)vessel;
	
}