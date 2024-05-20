// Auto generated code file.  Blender: 3.3.9  Blender Tools: (2, 1, 3)
// Date: Mon Apr 29 21:43:37 2024


#include "Orbitersdk.h"

#ifndef __747STdefinitions_H
#define __747STdefinitions_H


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
    const UINT Front_landing_gear_right_door_Id = 23;
    const UINT Front_landing_gear_left_door_Id = 24;
    const UINT Rear_right_landing_gear_door1_Id = 25;
    const UINT Rear_left_landing_gear_door1_Id = 26;
    const UINT Rear_right_landing_gear_door2_Id = 27;
    const UINT Rear_left_landing_gear_door2_Id = 28;
    const UINT Rear_left_wing_landing_gear_part_Id = 29;
    const UINT Rear_right_wing_landing_gear_part_Id = 30;
    const UINT ENG1_blades_Id = 31;
    const UINT ENG2_Id = 32;
    const UINT ENG3_Id = 33;
    const UINT ENG4_Id = 34;
    const UINT ENG2_blades_Id = 35;
    const UINT ENG3_blades_Id = 36;
    const UINT ENG4_blades_Id = 37;
    constexpr VECTOR3 Fuselage_Location =     {0.0000, 0.0000, 0.0000};
    constexpr VECTOR3 Vertical_stabilizer_Location =     {0.0262, 11.8905, -31.6377};
    constexpr VECTOR3 Right_stabilizer_Location =     {5.0978, 6.9979, -34.0662};
    constexpr VECTOR3 Right_wing_Location =     {8.9758, 4.0812, -1.1481};
    constexpr VECTOR3 Belly_Location =     {0.0033, 3.1852, 1.3906};
    constexpr VECTOR3 ENG1_Location =     {-20.1061, 2.6273, -4.5299};
    constexpr VECTOR3 Engines_attachment_Location =     {-0.1418, 3.9385, -3.1325};
    constexpr VECTOR3 Rear_left_landing_gear_Location =     {-2.0689, 0.6302, -1.8269};
    constexpr VECTOR3 Rear_left_wing_landing_gear_Location =     {-5.2835, 0.7292, -3.2305};
    constexpr VECTOR3 Pylons_Location =     {0.0133, 3.7530, -6.4755};
    constexpr VECTOR3 Front_landing_gear_Location =     {0.0195, 0.5888, 22.0522};
    constexpr VECTOR3 LAileron_Location =     {-23.9784, 5.3017, -14.2686};
    constexpr VECTOR3 Flaps_Location =     {-0.0182, 4.3694, -5.2389};
    constexpr VECTOR3 Right_elevator_trim_Location =     {4.4646, 7.0464, -36.3028};
    constexpr VECTOR3 Rudder_Location =     {0.0309, 12.0859, -36.2307};
    constexpr VECTOR3 Flaps2_Location =     {-0.0182, 4.8772, -9.5703};
    constexpr VECTOR3 Left_stabilizer_Location =     {-5.0667, 6.9979, -34.0664};
    constexpr VECTOR3 Left_elevator_trim_Location =     {-4.4334, 7.0464, -36.3028};
    constexpr VECTOR3 Left_wing_Location =     {-9.0107, 4.0791, -1.1772};
    constexpr VECTOR3 Rear_right_landing_gear_Location =     {2.0681, 0.6302, -1.8269};
    constexpr VECTOR3 Cockpit_windows_Location =     {0.0382, 8.4046, 24.3853};
    constexpr VECTOR3 Raileron_Location =     {23.9421, 5.3017, -14.2686};
    constexpr VECTOR3 Rear_right_wing_landing_gear_Location =     {5.2756, 0.7292, -3.2305};
    constexpr VECTOR3 Front_landing_gear_right_door_Location =     {1.2697, 2.0695, 22.9163};
    constexpr VECTOR3 Front_landing_gear_left_door_Location =     {-1.2013, 2.0614, 22.9163};
    constexpr VECTOR3 Rear_right_landing_gear_door1_Location =     {0.6332, 1.1428, -1.9929};
    constexpr VECTOR3 Rear_left_landing_gear_door1_Location =     {-0.5959, 1.1498, -1.9546};
    constexpr VECTOR3 Rear_right_landing_gear_door2_Location =     {0.5480, 0.8903, -2.1668};
    constexpr VECTOR3 Rear_left_landing_gear_door2_Location =     {-0.5046, 0.9094, -1.9445};
    constexpr VECTOR3 Rear_left_wing_landing_gear_part_Location =     {-4.4911, 1.8962, -3.3095};
    constexpr VECTOR3 Rear_right_wing_landing_gear_part_Location =     {4.4832, 1.8962, -3.3095};
    constexpr VECTOR3 ENG1_blades_Location =     {-20.1033, 2.6415, -3.5497};
    constexpr VECTOR3 ENG2_Location =     {-11.4136, 2.1305, 2.9770};
    constexpr VECTOR3 ENG3_Location =     {11.4315, 2.1305, 2.9770};
    constexpr VECTOR3 ENG4_Location =     {20.0279, 2.7650, -4.5420};
    constexpr VECTOR3 ENG2_blades_Location =     {-11.4068, 2.1021, 4.0353};
    constexpr VECTOR3 ENG3_blades_Location =     {11.4457, 2.1021, 4.0353};
    constexpr VECTOR3 ENG4_blades_Location =     {20.0302, 2.7799, -3.5497};
    constexpr VECTOR3 Water_discharge2_Location =     {0.0382, 1.8962, -12.1543};
    constexpr VECTOR3 Water_discharge1_Location =     {0.0382, 1.8962, -10.6543};
    constexpr VECTOR3 TDP1_Location =     {0.0229, 0.0052, 22.0571};
    constexpr VECTOR3 TDP2_Location =     {-5.3282, 0.0052, -16.2437};
    constexpr VECTOR3 TDP3_Location =     {5.3410, 0.0052, -16.2440};
    constexpr VECTOR3 TDP4_Location =     {0.0229, 3.1449, 26.4428};
    constexpr VECTOR3 TDP5_Location =     {0.0229, 5.3129, 29.8068};
    constexpr VECTOR3 TDP6_Location =     {0.0229, 2.8946, -21.2924};
    constexpr VECTOR3 TDP7_Location =     {0.0229, 6.3669, -37.0417};
    constexpr VECTOR3 TDP8_Location =     {10.8877, 7.8405, -39.0389};
    constexpr VECTOR3 TDP9_Location =     {-10.8419, 7.8405, -39.0389};
    constexpr VECTOR3 TDP10_Location =     {28.5192, 5.5548, -15.7323};
    constexpr VECTOR3 TDP11_Location =     {-28.4911, 5.5548, -15.7323};
    constexpr VECTOR3 TDP12_Location =     {0.0044, 19.0569, -39.8442};
    constexpr VECTOR3 TDP13_Location =     {0.0044, 9.4061, 8.5593};
    constexpr VECTOR3 TDP14_Location =     {0.0044, 9.5661, 23.1625};
    constexpr VECTOR3 Axis_elevator_right_Location =     {5.3257, 7.1061, -35.7319};
    constexpr VECTOR3 Axis_elevator_left_Location =     {-5.2743, 7.1061, -35.7319};
    constexpr VECTOR3 Axis_front_landing_gear_rotate_Location =     {0.0184, 2.3808, 22.0443};
    constexpr VECTOR3 Axis_front_landing_gear_right_door_Location =     {1.1942, 2.6628, 23.0713};
    constexpr VECTOR3 Axis_front_landing_gear_left_door_Location =     {-1.1259, 2.6628, 23.0707};
    constexpr VECTOR3 Axis_raileron_Location =     {23.9486, 5.2887, -13.8423};
    constexpr VECTOR3 Axis_laileron_Location =     {-24.0264, 5.2887, -13.8423};
    constexpr VECTOR3 Axis_rudder_Location =     {0.0299, 12.1379, -34.7588};
    constexpr VECTOR3 Axis_left_wing_landing_gear_Location =     {-5.5107, 3.5010, -3.3095};
    constexpr VECTOR3 Axis_rear_left_wing_landing_gear_part_Location =     {-3.8567, 2.5484, -3.3025};
    constexpr VECTOR3 Axis_rear_right_wing_landing_gear_part_Location =     {3.8440, 2.5484, -3.3025};
    constexpr VECTOR3 Axis_right_wing_landing_gear_Location =     {5.5013, 3.5010, -3.3092};
    constexpr VECTOR3 Axis_left_landing_gear_Location =     {-2.0722, 1.9285, -2.1531};
    constexpr VECTOR3 Axis_right_landing_gear_Location =     {2.0692, 1.9285, -2.1531};
    constexpr VECTOR3 Axis_landing_gear_left_door_1_Location =     {-0.5398, 1.8746, -1.9931};
    constexpr VECTOR3 Axis_left_landing_gear_door2_Location =     {-1.9882, 1.9285, -1.9377};
    constexpr VECTOR3 Axis_right_landing_gear_door2_Location =     {1.9816, 1.9285, -1.9377};
    constexpr VECTOR3 Axis_landing_gear_right_door_1_Location =     {0.5832, 1.8746, -1.9931};
    constexpr VECTOR3 LIGHT1_Location =     {-5.0761, 3.7022, 7.7683};
    constexpr VECTOR3 LIGHT2_Location =     {-4.3816, 3.6226, 8.3880};
    constexpr VECTOR3 LIGHT3_Location =     {4.3805, 3.6226, 8.3880};
    constexpr VECTOR3 LIGHT4_Location =     {4.9986, 3.7022, 7.7683};
    constexpr VECTOR3 Beacon2_right_wing_Location =     {28.6913, 5.5589, -13.5592};
    constexpr VECTOR3 Beacon1_left_wing_Location =     {-28.7126, 5.5589, -13.5592};
    constexpr VECTOR3 Beacon3_upper_deck_Location =     {0.0413, 9.5778, 16.5148};
    constexpr VECTOR3 Beacon4_belly_landing_gear_Location =     {0.0413, 1.7715, 4.7940};
    constexpr VECTOR3 Beacon5_APU_Location =     {0.0413, 6.9258, -37.7207};


#endif
