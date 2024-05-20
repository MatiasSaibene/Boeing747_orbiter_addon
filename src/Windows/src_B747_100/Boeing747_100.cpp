//Copyright (c) Matías Saibene
//Licenced under the MIT Licence

//==========================================
//          ORBITER MODULE: Boeing 747-100
//
//Boeing747_100.cpp
//Control module for Boeing 747-100 vessel class
//
//==========================================


#include <stdio.h>
#include <string.h>
#define ORBITER_MODULE
#include "Boeing747_100.h"
#include <cstring>
#include <cstdio>

bool parkingBrakeEnabled;
bool lights_on;
static int currentSkin = 0;
bool bGearIsDown;
bool engines_on;


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
	*cd = pd + oapiGetInducedDrag (*cl, B747100_VLIFT_A, 0.7) + oapiGetWaveDrag (M, 0.75, 1.0, 1.1, 0.04);
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
	*cd = 0.015 + oapiGetInducedDrag (*cl, B747100_HLIFT_A, 0.6) + oapiGetWaveDrag (M, 0.75, 1.0, 1.1, 0.04);
}


//Constructor
B747100::B747100(OBJHANDLE hVessel, int flightmodel) : 
VESSEL4(hVessel, flightmodel){

	landing_gear_proc = 0.0;

	landing_gear_status = GEAR_DOWN;

    engines_on = false;

	DefineAnimations();

    b747100_mesh = NULL;

    mhcockpit_mesh = NULL;

    fccabin_mesh = NULL;

    skinpath[0] = '\0';
    for (int i = 0; i < 5; i++)
        skin[i] = 0;

}

//Destructor
B747100::~B747100(){

}

void B747100::DefineAnimations(void){
    
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
}

// Overloaded callback functions
// Set the capabilities of the vessel class
void B747100::clbkSetClassCaps(FILEHANDLE cfg){

    //Physical vessel parameters
    SetSize(B747100_SIZE);
    SetEmptyMass(B747100_EMPTYMASS);
	SetCrossSections(B747100_CS);
	SetPMI(B747100_PMI);
	SetMaxWheelbrakeForce(89e3);
	SetRotDrag(_V(10, 10, 2.5));
	
	PROPELLANT_HANDLE JET_A1 = CreatePropellantResource(B747100_FUELMASS);

	th_main[0] = CreateThruster((ENG1_Location), _V(0, 0, 1), B747100_MAXMAINTH, JET_A1, B747100_ISP);
    th_main[1] = CreateThruster((ENG2_Location), _V(0, 0, 1), B747100_MAXMAINTH, JET_A1, B747100_ISP);
    th_main[2] = CreateThruster((ENG3_Location), _V(0, 0, 1), B747100_MAXMAINTH, JET_A1, B747100_ISP);
    th_main[3] = CreateThruster((ENG4_Location), _V(0, 0, 1), B747100_MAXMAINTH, JET_A1, B747100_ISP);
    thg_main = CreateThrusterGroup(th_main, 4, THGROUP_MAIN);

    th_retro[0] = CreateThruster((ENG1_Location), _V(0, 0, -1), (B747100_MAXMAINTH/4), JET_A1, B747100_ISP);
    th_retro[1] = CreateThruster((ENG2_Location), _V(0, 0, -1), (B747100_MAXMAINTH/4), JET_A1, B747100_ISP);
    th_retro[2] = CreateThruster((ENG3_Location), _V(0, 0, -1), (B747100_MAXMAINTH/4), JET_A1, B747100_ISP);
    th_retro[3] = CreateThruster((ENG4_Location), _V(0, 0, -1), (B747100_MAXMAINTH/4), JET_A1, B747100_ISP);
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

	lwing = CreateAirfoil3(LIFT_VERTICAL, (Left_wing_Location), VLiftCoeff, 0, B747100_VLIFT_C, (B747100_VLIFT_S*4), B747100_VLIFT_A);

    rwing = CreateAirfoil3(LIFT_VERTICAL,(Right_wing_Location), VLiftCoeff, 0, B747100_VLIFT_C,(B747100_VLIFT_S*4), B747100_VLIFT_A);

    lstabilizer = CreateAirfoil3(LIFT_VERTICAL, (Left_stabilizer_Location), VLiftCoeff, 0, B747100_STAB_C, B747100_STAB_S, B747100_STAB_A);

    rstabilizer = CreateAirfoil3(LIFT_VERTICAL, (Right_stabilizer_Location), VLiftCoeff, 0, B747100_STAB_C, B747100_STAB_S, B747100_STAB_A);
    
    CreateAirfoil3(LIFT_HORIZONTAL, (Rudder_Location), HLiftCoeff, 0, B747100_HLIFT_C, B747100_HLIFT_S, B747100_HLIFT_A);

    hlaileron = CreateControlSurface3(AIRCTRL_AILERON,8.3696, 1.7, (LAileron_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_raileron);
    hraileron = CreateControlSurface3(AIRCTRL_AILERON, 8.3696, 1.7, (Raileron_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_laileron);

    CreateControlSurface3(AIRCTRL_ELEVATOR, (14.4997*2), 1.7, (Left_elevator_trim_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_elevator);
    CreateControlSurface3(AIRCTRL_ELEVATOR, (14.4997*2), 1.7, (Right_elevator_trim_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_elevator);

    CreateControlSurface3(AIRCTRL_ELEVATORTRIM, (14.4997*2), 1.7, (Left_elevator_trim_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_elevator_trim);
    CreateControlSurface3(AIRCTRL_ELEVATORTRIM, (14.4997*2), 1.7, (Right_elevator_trim_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_elevator_trim);

    CreateControlSurface3(AIRCTRL_RUDDER, 20.6937, 1.7, (Rudder_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_rudder);

    //Add the mesh
    SetMeshVisibilityMode(AddMesh(b747100_mesh = oapiLoadMesh("Boeing747\\Boeing_747_100")), MESHVIS_EXTERNAL);

    //Add the mesh for the cockpit
    SetMeshVisibilityMode(AddMesh(mhcockpit_mesh = oapiLoadMeshGlobal("Boeing747\\Boeing_747_cockpit")), MESHVIS_VC);

    //Add the mesh for the First Class cabin
    SetMeshVisibilityMode(AddMesh(fccabin_mesh = oapiLoadMeshGlobal("Boeing747\\Boeing_747_first_class")), MESHVIS_VC);

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

void B747100::clbkVisualCreated(VISHANDLE vis, int refcount){

    visual = vis;

    b747100_dmesh = GetDevMesh(vis, 0);

    ApplyLivery();


}

void B747100::clbkVisualDestroyed(VISHANDLE vis, int refcount){

    visual = NULL;
    b747100_dmesh = NULL;

}

void B747100::NextSkin() {
    if (currentSkin >= 15) {
        currentSkin = 0;
    }

    ChangeLivery();
    currentSkin++;
}

void B747100::ChangeLivery() {
    
    char completedir_fus[256];
    char completedir_vs[256];
    char completedir_rw[256];
    char completedir_eng[256];
    char completedir_lw[256];
    char SKINLIST[][7] = {"SKIN1", "SKIN2", "SKIN3", "SKIN4", "SKIN5", "SKIN6", "SKIN7", "SKIN8", "SKIN9", "SKIN10", "SKIN11", "SKIN12", "SKIN13", "SKIN14", "SKIN15"};  //I have no idea why, but this works. Seriously.


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
    skin[3] = oapiLoadTexture(completedir_lw);
    skin[4] = oapiLoadTexture(completedir_eng);

    ApplyLivery();
}

void B747100::ApplyLivery(){

    if(!b747100_dmesh) return;

    if(skin[0]) oapiSetTexture(b747100_dmesh, 1, skin[0]);

    if(skin[1]) oapiSetTexture(b747100_dmesh, 2, skin[1]);

    if(skin[2]) oapiSetTexture(b747100_dmesh, 3, skin[2]);

    if(skin[3]) oapiSetTexture(b747100_dmesh, 8, skin[3]);

    if(skin[4]) oapiSetTexture(b747100_dmesh, 9, skin[4]);

}

void B747100::ParkingBrake(){

    if(!parkingBrakeEnabled){
        SetWheelbrakeLevel(1, 0, true);
        parkingBrakeEnabled = true;
    } else {
        SetWheelbrakeLevel(0, 0, true);
        parkingBrakeEnabled = false;
    }

}

void B747100::ActivateBeacons(){

    for(int i = 0; i < 5; i++){
		if(!beacon[i].active){
				beacon[i].active = true;
		} else {
				beacon[i].active = false;
		}
	}
}

void B747100::LightsControl(void){

    if(!lights_on){
        l1 = AddSpotLight((LIGHT1_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);
        l2 = AddSpotLight((LIGHT2_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);
        l3 = AddSpotLight((LIGHT3_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);
        l4 = AddSpotLight((LIGHT4_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);

        cpl1 = AddPointLight((PL1_Location), 1, 0.15, 0, 0.15, ccol_d, ccol_s, ccol_a);
        cpl1->SetVisibility(LightEmitter::VIS_COCKPIT);
        cpl2 = AddPointLight((PL2_Location), 1, 0.15, 0, 0.15, ccol_d, ccol_s, ccol_a);
        cpl2->SetVisibility(LightEmitter::VIS_COCKPIT);

        fcl1 = AddPointLight((FC_PL1_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl1->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl2 = AddPointLight((FC_PL2_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl2->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl3 = AddPointLight((FC_PL3_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl3->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl4 = AddPointLight((FC_PL4_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl4->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl5 = AddPointLight((FC_PL5_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl5->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl6 = AddPointLight((FC_PL6_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl6->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl7 = AddPointLight((FC_PL7_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl7->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl8 = AddPointLight((FC_PL8_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl8->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl9 = AddPointLight((FC_PL9_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl9->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl10 = AddPointLight((FC_PL10_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl10->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl11 = AddPointLight((FC_PL11_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl11->SetVisibility(LightEmitter::VIS_COCKPIT);
        fcl12 = AddPointLight((FC_PL12_Location), 1, 0.5, 0, 0.5, fccol_d, fccol_s, fccol_a);
        fcl12->SetVisibility(LightEmitter::VIS_COCKPIT);

        lights_on = true;
    } else {
        DelLightEmitter(l1);
        DelLightEmitter(l2);
        DelLightEmitter(l3);
        DelLightEmitter(l4);

        DelLightEmitter(cpl1);
        DelLightEmitter(cpl2);

        DelLightEmitter(fcl1);
        DelLightEmitter(fcl2);
        DelLightEmitter(fcl3);
        DelLightEmitter(fcl4);
        DelLightEmitter(fcl5);
        DelLightEmitter(fcl6);
        DelLightEmitter(fcl7);
        DelLightEmitter(fcl8);
        DelLightEmitter(fcl9);
        DelLightEmitter(fcl10);
        DelLightEmitter(fcl11);
        DelLightEmitter(fcl12);

        lights_on = false;
    }
}

void B747100::EnginesAutostart(void){

    engines_on = true;
    m_pXRSound->PlayWav(engines_start);
    
}

void B747100::EnginesAutostop(void){

    engines_on = false;
    m_pXRSound->PlayWav(engines_shutdown);
    
}

void B747100::UpdateEnginesStatus(){

    if(engines_on == true){
        thg_main = CreateThrusterGroup(th_main, 4, THGROUP_MAIN);

        thg_retro = CreateThrusterGroup(th_retro, 4, THGROUP_RETRO);

        pwr = GetThrusterLevel(thg_main);

    } else if (engines_on == false){
        DelThrusterGroup(thg_main);
        DelThrusterGroup(thg_retro);
        pwr = 0;
    }
}

bool B747100::clbkLoadVC(int id){

    switch(id){
        case 0 : //Commander
            SetCameraOffset(Captains_camera_Location);
            SetCameraDefaultDirection(_V(0, 0, 1));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(-1, 1, -1, 2);
        break;

        case 1 : //First officer
            SetCameraOffset(First_officer_camera_Location);
            SetCameraDefaultDirection(_V(0, 0, 1));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(0, -1, -1, 2);
        break;

        case 2: //Engineer
            SetCameraOffset(Engineer_camera_Location);
            SetCameraDefaultDirection(_V(1, 0, 0));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(1, -1, -1, 3);
            m_pXRSound->StopWav(cabin_ambiance);
        break;

        case 3: //First class cabin
            SetCameraOffset(Camera_FC_seat1_Location);
            SetCameraDefaultDirection(_V(0, 0, 1));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(8, -1, 2, 4);
            m_pXRSound->PlayWav(cabin_ambiance);
        break;

        case 4:
            SetCameraOffset(Camera_FC_seat2_Location);
            SetCameraDefaultDirection(_V(0, 0, 1));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(7, -1, 3, 5);
        break;

        case 5:
            SetCameraOffset(Camera_FC_seat3_Location);
            SetCameraDefaultDirection(_V(0, 0, 1));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(6, -1, 4, -1);
        break;

        case 6:
            SetCameraOffset(Camera_FC_seat4_Location);
            SetCameraDefaultDirection(_V(0, 0, 1));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(-1, 5, 7, -1);
        break;

        case 7:
            SetCameraOffset(Camera_FC_seat5_Location);
            SetCameraDefaultDirection(_V(0, 0, 1));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(-1, 4, 8, 6);
        break;

        case 8:
            SetCameraOffset(Camera_FC_seat6_Location);
            SetCameraDefaultDirection(_V(0, 0, 1));
            SetCameraRotationRange(RAD*120, RAD*120, RAD*60, RAD*60);
            oapiVCSetNeighbours(-1, 3, 2, 7);
        break;
    }

    return true; 

}

int B747100::clbkConsumeBufferedKey(DWORD key, bool down, char *kstate){

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
    if(down){
        if(KEYMOD_CONTROL(kstate)){
            switch(key){
                case OAPI_KEY_A:
                EnginesAutostart();
                return 1;

                case OAPI_KEY_E:
                EnginesAutostop();
                return 1;
            }
        }
    }
    return 0;
}

//Load landing gear status from scenario file
void B747100::clbkLoadStateEx(FILEHANDLE scn, void *vs){
    
    char *line;

    while(oapiReadScenario_nextline(scn, line)){
        if(!_strnicmp(line, "GEAR", 4)){
            sscanf_s(line+4, "%d%lf", (int *)&landing_gear_status, &landing_gear_proc);
            SetAnimation(anim_landing_gear, landing_gear_proc);
            if (landing_gear_proc == 1.0){
                bGearIsDown = true;
            } else {
                bGearIsDown = false;
            }
        } else if(!_strnicmp(line, "SKIN", 4)){
            sscanf_s(line+4, "%s", skinname);
            char fname[256];
            strcpy(fname, "Boeing_747\\B747SP\\Skins\\");
            strcat(fname, skinname);
            int n = strlen(fname); fname[n++] = '\\';

            strcpy(fname+n, "Fuselage.dds"); skin[0] = oapiLoadTexture(fname);

            strcpy(fname+n, "Vertical_stabilizer.dds"); skin[1] = oapiLoadTexture(fname);

            strcpy(fname+n, "Right_wing.dds"); skin[2] = oapiLoadTexture(fname);

            strcpy(fname+n, "Left_wing.dds"); skin[3] = oapiLoadTexture(fname);

            strcpy(fname+n, "ENG1.dds"); skin[4] = oapiLoadTexture(fname);

        } else {
            ParseScenarioLineEx(line, vs);
        }
    }
}

void B747100::clbkSaveState(FILEHANDLE scn){

    char cbuf[256];

    SaveDefaultState(scn);
    sprintf(cbuf, "%d %0.4f", landing_gear_status, landing_gear_proc);
    oapiWriteScenario_string(scn, "GEAR", cbuf);

    oapiWriteScenario_string (scn, "SKIN", skinname);    
}

//////////Logic for animations
void B747100::SetGearDown(void){
    ActivateLandingGear((landing_gear_status == GEAR_DOWN || landing_gear_status == GEAR_DEPLOYING) ?
        GEAR_STOWING : GEAR_DEPLOYING);
}

void B747100::ActivateLandingGear(LandingGearStatus action){
    landing_gear_status = action;
}

void B747100::UpdateLandingGearAnimation(double simdt) {
    if (landing_gear_status >= GEAR_DEPLOYING) {
        double da = simdt * LANDING_GEAR_OPERATING_SPEED;
        if (landing_gear_status == GEAR_DEPLOYING) {
            if (landing_gear_proc > 0.0) landing_gear_proc = max(0.0, landing_gear_proc - da);
            else landing_gear_status = GEAR_DOWN;
            SetTouchdownPoints(tdvtx_geardown, ntdvtx_geardown);
            bGearIsDown = true;
        } else {
            if (landing_gear_proc < 1.0) landing_gear_proc = min(1.0, landing_gear_proc + da);
            else landing_gear_status = GEAR_UP;
            SetTouchdownPoints(tdvtx_gearup, ntdvtx_gearup);
            bGearIsDown = false;
        }
        SetAnimation(anim_landing_gear, landing_gear_proc);
    }
}

void B747100::UpdateGearStatus(void){
    if(!bGearIsDown){
        SetTouchdownPoints(tdvtx_geardown, ntdvtx_geardown);
        SetNosewheelSteering(true);
    } else if (bGearIsDown){
        SetTouchdownPoints(tdvtx_gearup, ntdvtx_gearup);
        SetNosewheelSteering(false);
    }
}

double B747100::UpdateLvlEnginesContrail(){
    double machnumber = GetMachNumber();
    double altitude = GetAltitude();

    if((machnumber > 0.5) && ((altitude > 10000) && (altitude < 15000))){
        return 1.0;
    } else {
        return 0.0;
    }

}

void B747100::clbkPostStep(double simt, double simdt, double mjd){
    UpdateLandingGearAnimation(simdt);
    lvlcontrailengines = UpdateLvlEnginesContrail();
    UpdateEnginesStatus();
}

void B747100::clbkPostCreation(){

    UpdateGearStatus();

    m_pXRSound = XRSound::CreateInstance(this);

    m_pXRSound->LoadWav(engines_start, "XRSound\\Boeing747\\747_APU_Start.wav", XRSound::PlaybackType::BothViewFar);

    m_pXRSound->LoadWav(engines_shutdown, "XRSound\\Boeing747\\747_APU_Shutdown.wav", XRSound::PlaybackType::BothViewFar);

    m_pXRSound->LoadWav(XRSound::MainEngines, "XRSound\\Boeing747\\747_Engine.wav", XRSound::PlaybackType::BothViewFar);

    m_pXRSound->LoadWav(cabin_ambiance, "XRSound\\Boeing747\\747_cabin_ambiance.wav", XRSound::PlaybackType::InternalOnly);

    m_pXRSound->SetDefaultSoundEnabled(XRSound::MainEngines, "XRSound\\Boeing747\\747_Engine.wav");

    m_pXRSound->LoadWav(gear_movement, "XRSound\\Default\\Gear Whine.wav", XRSound::PlaybackType::BothViewMedium);

}

void B747100::clbkPreStep(double simt, double simdt, double mjd){

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

DLLCLBK void InitModule(HINSTANCE hModule){


}

DLLCLBK void ExitModule(HINSTANCE *hModule){

}



///////////////Vessel initialization

DLLCLBK VESSEL *ovcInit(OBJHANDLE hvessel, int flightmodel){
    
	return new B747100(hvessel, flightmodel);

}

/////////////Vessel memory cleanup
DLLCLBK void ovcExit(VESSEL *vessel){
    
	if(vessel) delete(B747100*)vessel;
	
}