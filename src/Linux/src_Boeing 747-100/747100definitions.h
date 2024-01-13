// Auto generated code file.  Blender: 3.3.9  Blender Tools: (2, 1, 3)
// Date: Sat Jan 13 15:42:00 2024


#include "Orbitersdk.h"

#ifndef __747100definitions_H
#define __747100definitions_H


    const int TXIDX_Fuselage_dds = 1;
    const int TXIDX_Vertical_stabilizer_dds = 2;
    const int TXIDX_Right_wing_dds = 3;
    const int TXIDX_ENG1_dds = 4;
    const int TXIDX_Metal_chrome_dds = 5;
    const int TXIDX_Rear_left_landing_gear_dds = 6;
    const int TXIDX_Rear_left_wing_landing_gear_dds = 7;
    const int TXIDX_Front_landing_gear_dds = 8;
    const int TXIDX_Left_wing_dds = 9;
    constexpr auto MESH_NAME = "Boeing_747_100";

    const UINT Fuselage_Id = 0;
    const UINT Vertical_stabilizer_Id = 1;
    const UINT Right_stabilizer_Id = 2;
    const UINT Right_wing_Id = 3;
    const UINT Belly_Id = 4;
    const UINT ENG1_Id = 5;
    const UINT Engines_attachment_Id = 6;
    const UINT Rear_left_landing_gear_Id = 7;
    const UINT Rear_left_wing_landing_gear_Id = 8;
    const UINT Pylons_Id = 9;
    const UINT Front_landing_gear_Id = 10;
    const UINT LAileron_Id = 11;
    const UINT Flaps_Id = 12;
    const UINT Right_elevator_trim_Id = 13;
    const UINT Rudder_Id = 14;
    const UINT Flaps2_Id = 15;
    const UINT Left_stabilizer_Id = 16;
    const UINT Left_elevator_trim_Id = 17;
    const UINT Left_wing_Id = 18;
    const UINT Rear_right_landing_gear_Id = 19;
    const UINT Cockpit_windows_Id = 20;
    const UINT Raileron_Id = 21;
    const UINT Rear_right_wing_landing_gear_Id = 22;
    const UINT ENG2_Id = 23;
    const UINT ENG3_Id = 24;
    const UINT ENG4_Id = 25;
    const UINT Front_landing_gear_right_door_Id = 26;
    const UINT Front_landing_gear_left_door_Id = 27;
    const UINT Rear_right_landing_gear_door1_Id = 28;
    const UINT Rear_left_landing_gear_door1_Id = 29;
    const UINT Rear_right_landing_gear_door2_Id = 30;
    const UINT Rear_left_landing_gear_door2_Id = 31;
    const UINT Rear_left_wing_landing_gear_part_Id = 32;
    const UINT Rear_right_wing_landing_gear_part_Id = 33;
    const UINT ENG1_blades_Id = 34;
    const UINT ENG2_blades_Id = 35;
    const UINT ENG3_blades_Id = 36;
    const UINT ENG4_blades_Id = 37;
    constexpr VECTOR3 Fuselage_Location =     {0.0407, 5.5787, 3.7052};
    constexpr VECTOR3 Vertical_stabilizer_Location =     {0.0301, 11.8905, -20.0546};
    constexpr VECTOR3 Right_stabilizer_Location =     {5.1018, 6.9979, -22.4832};
    constexpr VECTOR3 Right_wing_Location =     {8.9798, 4.0812, 10.4350};
    constexpr VECTOR3 Belly_Location =     {0.0073, 3.1470, 12.8536};
    constexpr VECTOR3 ENG1_Location =     {-20.1022, 2.6239, 7.0802};
    constexpr VECTOR3 Engines_attachment_Location =     {-0.1379, 3.9385, 8.4506};
    constexpr VECTOR3 Rear_left_landing_gear_Location =     {-2.0680, 1.9295, 9.4299};
    constexpr VECTOR3 Rear_left_wing_landing_gear_Location =     {-5.5066, 3.4997, 8.2749};
    constexpr VECTOR3 Pylons_Location =     {0.0172, 3.7530, 5.1076};
    constexpr VECTOR3 Front_landing_gear_Location =     {0.0234, 0.5888, 33.6353};
    constexpr VECTOR3 LAileron_Location =     {-23.9745, 5.3017, -2.6856};
    constexpr VECTOR3 Flaps_Location =     {-0.0142, 4.3694, 6.3442};
    constexpr VECTOR3 Right_elevator_trim_Location =     {4.4685, 7.0464, -24.7197};
    constexpr VECTOR3 Rudder_Location =     {0.0348, 12.0859, -24.6476};
    constexpr VECTOR3 Flaps2_Location =     {-0.0142, 4.8772, 2.0127};
    constexpr VECTOR3 Left_stabilizer_Location =     {-5.0627, 6.9979, -22.4833};
    constexpr VECTOR3 Left_elevator_trim_Location =     {-4.4295, 7.0464, -24.7197};
    constexpr VECTOR3 Left_wing_Location =     {-9.0067, 4.0791, 10.4059};
    constexpr VECTOR3 Rear_right_landing_gear_Location =     {0.5889, 1.8715, 9.5233};
    constexpr VECTOR3 Cockpit_windows_Location =     {0.0422, 8.4046, 35.9684};
    constexpr VECTOR3 Raileron_Location =     {23.9462, 5.5133, -2.2664};
    constexpr VECTOR3 Rear_right_wing_landing_gear_Location =     {5.2733, 0.7407, 8.3515};
    constexpr VECTOR3 ENG2_Location =     {-11.4096, 2.0827, 14.5992};
    constexpr VECTOR3 ENG3_Location =     {11.4354, 2.0827, 14.5992};
    constexpr VECTOR3 ENG4_Location =     {20.0319, 2.7646, 7.0802};
    constexpr VECTOR3 Front_landing_gear_right_door_Location =     {1.1982, 2.6628, 34.6537};
    constexpr VECTOR3 Front_landing_gear_left_door_Location =     {-1.1219, 2.6628, 34.6537};
    constexpr VECTOR3 Rear_right_landing_gear_door1_Location =     {0.5889, 1.8715, 9.5233};
    constexpr VECTOR3 Rear_left_landing_gear_door1_Location =     {-0.5358, 1.8746, 9.6092};
    constexpr VECTOR3 Rear_right_landing_gear_door2_Location =     {0.5656, 0.9535, 9.3867};
    constexpr VECTOR3 Rear_left_landing_gear_door2_Location =     {-0.5358, 1.8746, 9.5900};
    constexpr VECTOR3 Rear_left_wing_landing_gear_part_Location =     {-3.8527, 2.5484, 8.2806};
    constexpr VECTOR3 Rear_right_wing_landing_gear_part_Location =     {5.2733, 0.7407, 8.3515};
    constexpr VECTOR3 ENG1_blades_Location =     {-20.1022, 2.6178, 8.9148};
    constexpr VECTOR3 ENG2_blades_Location =     {-11.4028, 2.1021, 15.6184};
    constexpr VECTOR3 ENG3_blades_Location =     {11.4496, 2.1014, 15.6412};
    constexpr VECTOR3 ENG4_blades_Location =     {20.0341, 2.7799, 8.0295};
    constexpr VECTOR3 TDP1_Location =     {0.0268, 0.0052, 33.6402};
    constexpr VECTOR3 TDP2_Location =     {-5.3242, 0.0052, -4.6606};
    constexpr VECTOR3 TDP3_Location =     {5.3449, 0.0052, -4.6609};
    constexpr VECTOR3 TDP4_Location =     {0.0268, 3.1449, 38.0259};
    constexpr VECTOR3 TDP5_Location =     {0.0268, 5.3129, 41.3899};
    constexpr VECTOR3 TDP6_Location =     {0.0268, 2.8946, -9.7093};
    constexpr VECTOR3 TDP7_Location =     {0.0268, 6.3669, -25.4586};
    constexpr VECTOR3 TDP8_Location =     {10.8916, 7.8405, -27.4558};
    constexpr VECTOR3 TDP9_Location =     {-10.8380, 7.8405, -27.4558};
    constexpr VECTOR3 TDP10_Location =     {28.6831, 5.5548, -4.1492};
    constexpr VECTOR3 TDP11_Location =     {-28.6671, 5.5548, -4.1492};
    constexpr VECTOR3 TDP12_Location =     {0.0083, 19.0569, -28.2611};
    constexpr VECTOR3 TDP13_Location =     {0.0083, 9.5661, 25.5424};
    constexpr VECTOR3 TDP14_Location =     {0.0083, 9.5661, 34.7456};
    constexpr VECTOR3 Axis_elevator_right_Location =     {5.3297, 7.1061, -24.1488};
    constexpr VECTOR3 Axis_elevator_left_Location =     {-5.2703, 7.1061, -24.1488};
    constexpr VECTOR3 Axis_front_landing_gear_rotate_Location =     {0.0223, 2.3808, 33.6274};
    constexpr VECTOR3 Axis_front_landing_gear_right_door_Location =     {1.1982, 2.6628, 34.6544};
    constexpr VECTOR3 Axis_front_landing_gear_left_door_Location =     {-1.1219, 2.6628, 34.6537};
    constexpr VECTOR3 Axis_raileron_Location =     {23.9526, 5.2887, -2.2592};
    constexpr VECTOR3 Axis_laileron_Location =     {-24.0225, 5.2887, -2.2592};
    constexpr VECTOR3 Axis_rudder_Location =     {0.0339, 12.1379, -23.1758};
    constexpr VECTOR3 Axis_left_wing_landing_gear_Location =     {-5.5068, 3.5010, 8.2736};
    constexpr VECTOR3 Axis_rear_left_wing_landing_gear_part_Location =     {-3.8527, 2.5484, 8.2806};
    constexpr VECTOR3 Axis_rear_right_wing_landing_gear_part_Location =     {3.8480, 2.5484, 8.2806};
    constexpr VECTOR3 Axis_right_wing_landing_gear_Location =     {5.5053, 3.5010, 8.2739};
    constexpr VECTOR3 Axis_left_landing_gear_Location =     {-2.0682, 1.9285, 9.4300};
    constexpr VECTOR3 Axis_right_landing_gear_Location =     {2.0732, 1.9285, 9.4300};
    constexpr VECTOR3 Axis_landing_gear_left_door_1_Location =     {-0.5358, 1.8746, 9.5900};
    constexpr VECTOR3 Axis_left_landing_gear_door2_Location =     {-1.9843, 1.9285, 9.6454};
    constexpr VECTOR3 Axis_right_landing_gear_door2_Location =     {1.9855, 1.9285, 9.6454};
    constexpr VECTOR3 Axis_landing_gear_right_door_1_Location =     {0.5872, 1.8746, 9.5900};


#endif
