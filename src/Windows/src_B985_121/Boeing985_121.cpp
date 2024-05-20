//Copyright (c) Matías Saibene
//Licenced under the MIT Licence

//==========================================
//          ORBITER MODULE: Boeing 747 YAL1
//
//Boeing747_YAL1.cpp
//Control module for Boeing 747YAL1 vessel class
//
//==========================================

#define ORBITER_MODULE
#include "Boeing985_121.h"
#include <cstring>
#include <cstdio>

bool parkingBrakeEnabled;
bool lights_on;


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
	*cd = pd + oapiGetInducedDrag (*cl, B985121_VLIFT_A, 0.7) + oapiGetWaveDrag (M, 0.75, 1.0, 1.1, 0.04);
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
	*cd = 0.015 + oapiGetInducedDrag (*cl, B985121_HLIFT_A, 0.6) + oapiGetWaveDrag (M, 0.75, 1.0, 1.1, 0.04);
}

//Constructor
B985121::B985121(OBJHANDLE hVessel, int flightmodel) : VESSEL4(hVessel, flightmodel){

	DefineAnimations();

    B985121_mesh = NULL;

    //SetTouchdownPoints(tdvtx_gearup,ntdvtx_gearup);

}

//Destructor
B985121::~B985121(){

}

void B985121::DefineAnimations(void){

    //Control surfaces

    static unsigned int LeftElevatorGrp[1] = {LAileron_Id};
    static MGROUP_ROTATE LeftElevator(
        0,
        LeftElevatorGrp,
        1,
        (Axis_laileron_Location),
        _V(1, 0, 0),
        (float)(45*RAD)
    );

    static unsigned int RightElevatorGrp[1] = {RAileron_Id};
    static MGROUP_ROTATE RightElevator(
        0,
        RightElevatorGrp,
        1,
        (Axis_raileron_Location),
        _V(1, 0, -0.5),
        (float)(45*RAD)
    );

    anim_elevator = CreateAnimation(0.5);
    AddAnimationComponent(anim_elevator, 0, 1, &LeftElevator);
    AddAnimationComponent(anim_elevator, 0, 1, &RightElevator);


    static unsigned int LeftElevatorTrimGrp[1] = {LAileron_Id};
    static MGROUP_ROTATE LeftElevatorTrim(
        0,
        LeftElevatorTrimGrp,
        1,
        (Axis_laileron_Location),
        _V(1, 0, 0),
        (float)(22.5*RAD)
    );

    static unsigned int RightElevatorTrimGrp[1] = {RAileron_Id};
    static MGROUP_ROTATE RightElevatorTrim(
        0,
        RightElevatorTrimGrp,
        1,
        (Axis_raileron_Location),
        _V(1, 0, 0),
        (float)(22.5*RAD)
    );

    anim_elevator_trim = CreateAnimation(0.5);
    AddAnimationComponent(anim_elevator, 0, 1, &LeftElevatorTrim);
    AddAnimationComponent(anim_elevator, 0, 1, &RightElevatorTrim);


    static unsigned int LeftAileronGrp[1] = {LAileron_Id};
    static MGROUP_ROTATE LeftAileron(
        0,
        LeftAileronGrp,
        1,
        (Axis_laileron_Location),
        _V(1, 0, 0),
        (float)(45*RAD)
    );

    static unsigned int RightAileronGrp[1] = {RAileron_Id};
    static MGROUP_ROTATE RightAileron(
        0,
        RightAileronGrp,
        1,
        (Axis_raileron_Location),
        _V(1, 0, 0),
        (float)(45*RAD)
    );

    anim_laileron = CreateAnimation(0.5);
    anim_raileron = CreateAnimation(0.5);
    AddAnimationComponent(anim_laileron, 0, 1, &LeftAileron);
    AddAnimationComponent(anim_raileron, 0, 1, &RightAileron);

    static unsigned int LeftUpperRudderGrp[1] = {Upper_left_rudder_Id};
    static MGROUP_ROTATE LeftUpperRudder(
        0,
        LeftUpperRudderGrp,
        1,
        (Axis_upper_left_vs_Location),
        _V(0, 1, 0),
        (float)(22.5*RAD)
    );

    static unsigned int LeftLowerRudderGrp[1] = {Lower_left_rudder_Id};
    static MGROUP_ROTATE LeftLowerRudder(
        0,
        LeftLowerRudderGrp,
        1,
        (Axis_lower_left_vs_Location),
        _V(0, 1, 0),
        (float)(22.5*RAD)
    );

    static unsigned int RightUpperRudderGrp[1] = {Upper_right_rudder_Id};
    static MGROUP_ROTATE RightUpperRudder(
        0,
        RightUpperRudderGrp,
        1,
        (Axis_upper_right_vs_Location),
        _V(0, 1, 0),
        (float)(22.5*RAD)
    );

    static unsigned int RightLowerRudderGrp[1] = {Lower_right_rudder_Id};
    static MGROUP_ROTATE RightLowerRudder(
        0,
        RightLowerRudderGrp,
        1,
        (Axis_lower_right_vs_Location),
        _V(0, 1, 0),
        (float)(22.5*RAD)
    );

    anim_rudder = CreateAnimation(0.5);
    AddAnimationComponent(anim_rudder, 0, 1, &LeftUpperRudder);
    AddAnimationComponent(anim_rudder, 0, 1, &LeftLowerRudder);
    AddAnimationComponent(anim_rudder, 0, 1, &RightUpperRudder);
    AddAnimationComponent(anim_rudder, 0, 1, &RightLowerRudder);


}

void B985121::clbkSetClassCaps(FILEHANDLE cfg){

    //Physical vessel parameters
    SetSize(B985121_SIZE);
    SetEmptyMass(B985121_EMPTYMASS);
    SetCrossSections(B985121_CS);
    SetPMI(B985121_PMI);
    SetMaxWheelbrakeForce(89e3);
    SetRotDrag(_V(10, 10, 2.5));
    SetTouchdownPoints(tdvtx_gearup,ntdvtx_gearup);
    dock = CreateDock(TDP1_Location, _V(0, 0, 1), _V(1, 0, 0));

    PROPELLANT_HANDLE JET_A1 = CreatePropellantResource(B985121_FUELMASS);

    
	th_main = CreateThruster((Engine_Location), _V(0, 0, 1), B985121_MAXMAINTH, JET_A1, B985121_ISP);
    thg_main = CreateThrusterGroup(&th_main, 1, THGROUP_MAIN);
    exhaust_tex = oapiRegisterExhaustTexture("Exhaust");
    AddExhaust(th_main, 15, 1, (Engine_Location), _V(0, 0, -1), exhaust_tex);


	hwing = CreateAirfoil3(LIFT_VERTICAL, _V(0, 0, 0), VLiftCoeff, 0, B985121_VLIFT_C, B985121_VLIFT_S*2, B985121_VLIFT_A);

    lstabilizer = CreateAirfoil3(LIFT_HORIZONTAL, (Left_vertical_stab_Location), HLiftCoeff, 0, B985121_HLIFT_C, B985121_HLIFT_S, B985121_HLIFT_A);


    rstabilizer = CreateAirfoil3(LIFT_HORIZONTAL, (Right_vertical_stab_Location), HLiftCoeff, 0, B985121_HLIFT_C, B985121_HLIFT_S, B985121_HLIFT_A);


    hlaileron = CreateControlSurface3(AIRCTRL_AILERON,0.8480, 1.7, (LAileron_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_raileron);


    hraileron = CreateControlSurface3(AIRCTRL_AILERON, 0.8480, 1.7, (RAileron_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_laileron);

    CreateControlSurface3(AIRCTRL_ELEVATOR, 1.6961, 1.7, (Elevator_Location), AIRCTRL_AXIS_XPOS, 1.0, anim_elevator);

    CreateControlSurface3(AIRCTRL_ELEVATORTRIM, 1.6961, 1.7, (Elevator_Location), AIRCTRL_AXIS_XPOS, 1.0, anim_elevator);

    CreateControlSurface3(AIRCTRL_RUDDER, 3.2524, 1.7, (Engine_Location), AIRCTRL_AXIS_AUTO, 1.0, anim_rudder);

    //Add the mesh
    SetMeshVisibilityMode (AddMesh (B985121_mesh = oapiLoadMeshGlobal ("Boeing747\\Boeing_985_121")), MESHVIS_EXTERNAL);


    //Define beacons

    static VECTOR3 beaconpos[5] = {{Beacon1_Location}, {Beacon2_Location}, {Beacon3_Location}, {Beacon4_Location}, {Beacon5_Location}};
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

    //Sound speed barrier visual effect
	static PARTICLESTREAMSPEC soundbarrierpart = {
		0, 30.0, 15, 350, 0.15, 1, 2, 1, 
		PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 2,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-4, 1
	};
	static VECTOR3 pos = {0, 0, 0};
	static VECTOR3 dir = {0, 0, -1};
	AddParticleStream(&soundbarrierpart, pos, dir, &lvl);

}


void B985121::ActivateBeacons(){

    for(int i = 0; i < 5; i++){
		if(!beacon[i].active){
				beacon[i].active = true;
		} else {
				beacon[i].active = false;
		}
	}
}

void B985121::LightsControl(void){

    if(!lights_on){
        l1 = AddSpotLight((LIGHT1_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);
        l2 = AddSpotLight((LIGHT2_Location), _V(0, 0, 1), 10000, 1e-3, 0, 2e-3, 25*RAD, 45*RAD, col_d, col_s, col_a);

        lights_on = true;
    } else {
        DelLightEmitter(l1);
        DelLightEmitter(l2);

        lights_on = false;
    }
}


int B985121::clbkConsumeBufferedKey(DWORD key, bool down, char *kstate){

    if(key == OAPI_KEY_B && down){
        ActivateBeacons();
        return 1;
    }
    if(key == OAPI_KEY_F && down){
        LightsControl();
        return 1;
    }
    return 0;
}


void B985121::clbkPostStep(double simt, double simdt, double mjd){
    lvl = UpdateParticleLvl();

    //SetTouchdownPoints(tdvtx_gearup,ntdvtx_gearup);

}


double B985121::UpdateParticleLvl(){
	double machnumber = GetMachNumber();

	if((machnumber >= 0.999) && (machnumber <= 1.001)){
		return 1.0;
	} else {
		return 0.0;
	}
}

////////////////////////

DLLCLBK void InitModule(HINSTANCE hModule){


}

DLLCLBK void ExitModule(HINSTANCE *hModule){

}



///////////////Vessel initialization

DLLCLBK VESSEL *ovcInit(OBJHANDLE hvessel, int flightmodel){
    
	return new B985121(hvessel, flightmodel);

}

/////////////Vessel memory cleanup
DLLCLBK void ovcExit(VESSEL *vessel){
    
	if(vessel) delete(B985121*)vessel;
	
}