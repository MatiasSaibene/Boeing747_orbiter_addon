// Auto generated code file.  Blender: 3.3.9  Blender Tools: (2, 1, 3)
// Date: Mon Mar 18 21:43:37 2024


#include "Orbitersdk.h"

#ifndef __747SOFIAdefinitions_H
#define __747SOFIAdefinitions_H


    const UINT Fuselage_Id = 0;
    const UINT Vertical_stabilizer_Id = 1;
    const UINT Right_stabilizer_Id = 2;
    const UINT Right_wing_Id = 3;
    const UINT Belly_Id = 4;
    const UINT Engines_attachment_Id = 5;
    const UINT Rear_left_landing_gear_Id = 6;
    const UINT Rear_left_wing_landing_gear_Id = 7;
    const UINT Pylons_Id = 8;
    const UINT Front_landing_gear_Id = 9;
    const UINT LAileron_Id = 10;
    const UINT Flaps_Id = 11;
    const UINT Right_elevator_trim_Id = 12;
    const UINT Rudder_Id = 13;
    const UINT Flaps2_Id = 14;
    const UINT Left_stabilizer_Id = 15;
    const UINT Left_elevator_trim_Id = 16;
    const UINT Left_wing_Id = 17;
    const UINT Rear_right_landing_gear_Id = 18;
    const UINT Cockpit_windows_Id = 19;
    const UINT Raileron_Id = 20;
    const UINT PSGR_door6_Id = 21;
    const UINT PSGR_door7_Id = 22;
    const UINT PSGR_door8_Id = 23;
    const UINT PSGR_door9_Id = 24;
    const UINT PSGR_door10_Id = 25;
    const UINT PSGR_door1_Id = 26;
    const UINT PSGR_door2_Id = 27;
    const UINT PSGR_door3_Id = 28;
    const UINT PSGR_door4_Id = 29;
    const UINT PSGR_door5_Id = 30;
    const UINT Rear_right_wing_landing_gear_Id = 31;
    const UINT CRG_door3_Id = 32;
    const UINT CRG_door4_Id = 33;
    const UINT CRG_door2_Id = 34;
    const UINT CRG_door1_Id = 35;
    const UINT Front_landing_gear_right_door_Id = 36;
    const UINT Front_landing_gear_left_door_Id = 37;
    const UINT Rear_right_landing_gear_door1_Id = 38;
    const UINT Rear_left_landing_gear_door1_Id = 39;
    const UINT Rear_right_landing_gear_door2_Id = 40;
    const UINT Rear_left_landing_gear_door2_Id = 41;
    const UINT Rear_left_wing_landing_gear_part_Id = 42;
    const UINT Rear_right_wing_landing_gear_part_Id = 43;
    const UINT Telescope_hatch_Id = 44;
    const UINT Telescope_Id = 45;
    const UINT ENG1_Id = 46;
    const UINT ENG1_blades_Id = 47;
    const UINT ENG4_Id = 48;
    const UINT ENG4_blades_Id = 49;
    const UINT ENG2_Id = 50;
    const UINT ENG2_blades_Id = 51;
    const UINT ENG3_Id = 52;
    const UINT ENG3_blades_Id = 53;
    constexpr VECTOR3 Fuselage_Location =     {0.0407, 5.5787, 3.7052};
    constexpr VECTOR3 Vertical_stabilizer_Location =     {0.0301, 11.8905, -20.0546};
    constexpr VECTOR3 Right_stabilizer_Location =     {5.1018, 6.9979, -22.4832};
    constexpr VECTOR3 Right_wing_Location =     {8.9798, 4.0812, 2.4350};
    constexpr VECTOR3 Belly_Location =     {0.0073, 3.1470, 4.8536};
    constexpr VECTOR3 Engines_attachment_Location =     {-0.1379, 3.9385, 0.4506};
    constexpr VECTOR3 Rear_left_landing_gear_Location =     {-2.0680, 1.9295, 1.4299};
    constexpr VECTOR3 Rear_left_wing_landing_gear_Location =     {-5.5066, 3.4997, 0.2749};
    constexpr VECTOR3 Pylons_Location =     {0.0172, 3.7530, -2.8924};
    constexpr VECTOR3 Front_landing_gear_Location =     {0.0234, 0.5888, 20.2353};
    constexpr VECTOR3 LAileron_Location =     {-23.9745, 5.3017, -10.6856};
    constexpr VECTOR3 Flaps_Location =     {-0.0142, 4.3694, -1.6558};
    constexpr VECTOR3 Right_elevator_trim_Location =     {4.4685, 7.0464, -24.7197};
    constexpr VECTOR3 Rudder_Location =     {0.0348, 12.0859, -24.6476};
    constexpr VECTOR3 Flaps2_Location =     {-0.0142, 4.8772, -5.9873};
    constexpr VECTOR3 Left_stabilizer_Location =     {-5.0627, 6.9979, -22.4833};
    constexpr VECTOR3 Left_elevator_trim_Location =     {-4.4295, 7.0464, -24.7197};
    constexpr VECTOR3 Left_wing_Location =     {-9.0067, 4.0791, 2.4059};
    constexpr VECTOR3 Rear_right_landing_gear_Location =     {0.5889, 1.8715, 1.5233};
    constexpr VECTOR3 Cockpit_windows_Location =     {0.0422, 8.4046, 22.5669};
    constexpr VECTOR3 Raileron_Location =     {23.9462, 5.5133, -10.2664};
    constexpr VECTOR3 PSGR_door6_Location =     {1.9464, 8.0898, 20.1702};
    constexpr VECTOR3 PSGR_door7_Location =     {2.7956, 5.6785, 18.7923};
    constexpr VECTOR3 PSGR_door8_Location =     {2.9071, 5.6769, 12.2617};
    constexpr VECTOR3 PSGR_door9_Location =     {2.7980, 5.6775, -3.2411};
    constexpr VECTOR3 PSGR_door10_Location =     {2.4623, 5.6513, -13.8105};
    constexpr VECTOR3 PSGR_door1_Location =     {-1.8607, 8.0929, 20.1688};
    constexpr VECTOR3 PSGR_door2_Location =     {-2.7113, 5.6797, 18.7932};
    constexpr VECTOR3 PSGR_door3_Location =     {-2.8221, 5.6803, 12.2593};
    constexpr VECTOR3 PSGR_door4_Location =     {-2.7121, 5.6823, -3.2373};
    constexpr VECTOR3 PSGR_door5_Location =     {-2.3787, 5.6574, -13.8126};
    constexpr VECTOR3 Rear_right_wing_landing_gear_Location =     {5.2733, 0.7407, 0.3515};
    constexpr VECTOR3 CRG_door3_Location =     {2.4377, 3.5692, 16.4910};
    constexpr VECTOR3 CRG_door4_Location =     {2.4974, 3.6821, -7.5331};
    constexpr VECTOR3 CRG_door2_Location =     {-2.4116, 3.6771, -7.5225};
    constexpr VECTOR3 CRG_door1_Location =     {-2.3467, 3.5536, 16.4793};
    constexpr VECTOR3 Front_landing_gear_right_door_Location =     {1.1982, 2.6628, 21.2537};
    constexpr VECTOR3 Front_landing_gear_left_door_Location =     {-1.1219, 2.6628, 21.2537};
    constexpr VECTOR3 Rear_right_landing_gear_door1_Location =     {0.5889, 1.8715, 1.5233};
    constexpr VECTOR3 Rear_left_landing_gear_door1_Location =     {-0.5358, 1.8746, 1.5900};
    constexpr VECTOR3 Rear_right_landing_gear_door2_Location =     {0.5656, 0.9535, 1.3867};
    constexpr VECTOR3 Rear_left_landing_gear_door2_Location =     {-0.5358, 1.8746, 1.5900};
    constexpr VECTOR3 Rear_left_wing_landing_gear_part_Location =     {-3.8527, 2.5484, 0.2806};
    constexpr VECTOR3 Rear_right_wing_landing_gear_part_Location =     {5.2733, 0.7407, 0.3515};
    constexpr VECTOR3 Cockpit_offset_Location =     {0.0422, 8.4046, 22.5669};
    constexpr VECTOR3 Telescope_hatch_Location =     {-0.8485, 6.4755, -8.8223};
    constexpr VECTOR3 Telescope_Location =     {0.0407, 5.5787, 3.7052};
    constexpr VECTOR3 ENG1_Location =     {-20.1061, 2.6273, -0.9299};
    constexpr VECTOR3 ENG1_blades_Location =     {-20.1033, 2.6415, 0.0503};
    constexpr VECTOR3 ENG4_Location =     {19.8432, 2.6273, -0.9299};
    constexpr VECTOR3 ENG4_blades_Location =     {19.8460, 2.6415, 0.0503};
    constexpr VECTOR3 ENG2_Location =     {-11.5150, 1.9170, 6.4604};
    constexpr VECTOR3 ENG2_blades_Location =     {-11.5122, 1.9312, 7.4406};
    constexpr VECTOR3 ENG3_Location =     {11.2471, 1.9170, 6.4604};
    constexpr VECTOR3 ENG3_blades_Location =     {11.2499, 1.9312, 7.4406};
    constexpr VECTOR3 TDP1_Location =     {0.0268, 0.0052, 20.2402};
    constexpr VECTOR3 TDP2_Location =     {-5.3242, 0.0052, -12.6606};
    constexpr VECTOR3 TDP3_Location =     {5.3449, 0.0052, -12.7062};
    constexpr VECTOR3 TDP4_Location =     {0.0268, 3.1449, 24.6259};
    constexpr VECTOR3 TDP5_Location =     {0.0268, 5.3129, 27.9899};
    constexpr VECTOR3 TDP6_Location =     {0.0268, 2.8946, -9.7093};
    constexpr VECTOR3 TDP7_Location =     {0.0268, 6.3669, -25.4586};
    constexpr VECTOR3 TDP8_Location =     {10.8916, 7.8405, -27.4558};
    constexpr VECTOR3 TDP9_Location =     {-10.8380, 7.8405, -27.4558};
    constexpr VECTOR3 TDP10_Location =     {28.6831, 5.5548, -12.1492};
    constexpr VECTOR3 TDP11_Location =     {-28.6671, 5.5548, -12.1492};
    constexpr VECTOR3 TDP12_Location =     {0.0083, 19.0569, -28.2611};
    constexpr VECTOR3 TDP13_Location =     {0.0083, 9.5661, 11.5424};
    constexpr VECTOR3 TDP14_Location =     {0.0083, 9.5661, 20.7456};
    constexpr VECTOR3 Axis_elevator_right_Location =     {5.3297, 7.1061, -24.1488};
    constexpr VECTOR3 Axis_elevator_left_Location =     {-5.2703, 7.1061, -24.1488};
    constexpr VECTOR3 Axis_front_landing_gear_rotate_Location =     {0.0268, 2.3808, 20.2276};
    constexpr VECTOR3 Axis_front_landing_gear_right_door_Location =     {1.1982, 2.6628, 21.2537};
    constexpr VECTOR3 Axis_front_landing_gear_left_door_Location =     {-1.1219, 2.6628, 21.2537};
    constexpr VECTOR3 Axis_raileron_Location =     {23.9526, 5.2887, -10.2592};
    constexpr VECTOR3 Axis_laileron_Location =     {-24.0225, 5.2887, -10.2592};
    constexpr VECTOR3 Axis_rudder_Location =     {0.0339, 12.1379, -23.1758};
    constexpr VECTOR3 Axis_left_wing_landing_gear_Location =     {-5.5068, 3.5010, 0.2740};
    constexpr VECTOR3 Axis_rear_left_wing_landing_gear_part_Location =     {-3.8527, 2.5484, 0.2806};
    constexpr VECTOR3 Axis_rear_right_wing_landing_gear_part_Location =     {3.8480, 2.5484, 0.2806};
    constexpr VECTOR3 Axis_right_wing_landing_gear_Location =     {5.5053, 3.5010, 0.2740};
    constexpr VECTOR3 Axis_left_landing_gear_Location =     {-2.0682, 1.9285, 1.4300};
    constexpr VECTOR3 Axis_right_landing_gear_Location =     {2.0732, 1.9285, 1.4300};
    constexpr VECTOR3 Axis_landing_gear_left_door_1_Location =     {-0.5358, 1.8746, 1.5900};
    constexpr VECTOR3 Axis_left_landing_gear_door2_Location =     {-1.9843, 1.9285, 1.6454};
    constexpr VECTOR3 Axis_right_landing_gear_door2_Location =     {1.9855, 1.9285, 1.6454};
    constexpr VECTOR3 Axis_landing_gear_right_door_1_Location =     {0.5872, 1.8746, 1.5900};
    constexpr VECTOR3 Axis_telescope_Location =     {0.0407, 5.5787, -8.7948};
    constexpr VECTOR3 Beacon2_right_wing_Location =     {28.6913, 5.5589, -10.0592};
    constexpr VECTOR3 Beacon1_left_wing_Location =     {-28.7126, 5.5589, -10.0592};
    constexpr VECTOR3 Beacon3_upper_deck_Location =     {0.0413, 9.5778, 16.5148};
    constexpr VECTOR3 Beacon4_belly_landing_gear_Location =     {0.0413, 1.7715, 4.7940};
    constexpr VECTOR3 Beacon5_APU_Location =     {0.0413, 6.3946, -25.5689};
    constexpr VECTOR3 LIGHT2_Location =     {-4.0002, 3.5567, 12.3066};
    constexpr VECTOR3 LIGHT1_Location =     {-5.0002, 3.5567, 11.4303};
    constexpr VECTOR3 LIGHT3_Location =     {4.0000, 3.5567, 12.3066};
    constexpr VECTOR3 LIGHT4_Location =     {4.9998, 3.5567, 11.4303};


#endif
