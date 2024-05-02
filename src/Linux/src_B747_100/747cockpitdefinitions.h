// Auto generated code file.  Blender: 3.3.9  Blender Tools: (2, 1, 3)
// Date: Sat Feb 10 18:35:18 2024

#pragma once

#include "Orbitersdk.h"

#ifndef __747cockpitdefinitions_H
#define __747cockpitdefinitions_H


    const UINT Autopilot_panel_Id = 0;
    const UINT Autopilot_screen1_Id = 1;
    const UINT Autopilot_screen2_Id = 2;
    const UINT Autopilot_screen3_Id = 3;
    const UINT Autopilot_screen4_Id = 4;
    const UINT Brake_lever_Id = 5;
    const UINT Captain_seat_Id = 6;
    const UINT Central_pedestal_Id = 7;
    const UINT Central_pedestal_MFD1_Id = 8;
    const UINT Central_pedestal_MFD2_Id = 9;
    const UINT Central_pedestal_MFD3_Id = 10;
    const UINT Cockpit_fuselage_Id = 11;
    const UINT Engineer_panel_Id = 12;
    const UINT Engineer_seat_Id = 13;
    const UINT First_officer_seat_Id = 14;
    const UINT Flaps_lever_Id = 15;
    const UINT LYoke_Id = 16;
    const UINT LYoke_column_Id = 17;
    const UINT LYoke_column_pedestal_Id = 18;
    const UINT Landing_gear_lever_Id = 19;
    const UINT MFD1_Id = 20;
    const UINT MFD1_BTN1_Id = 21;
    const UINT MFD1_BTN10_Id = 22;
    const UINT MFD1_BTN11_Id = 23;
    const UINT MFD1_BTN12_Id = 24;
    const UINT MFD1_BTN2_Id = 25;
    const UINT MFD1_BTN3_Id = 26;
    const UINT MFD1_BTN4_Id = 27;
    const UINT MFD1_BTN5_Id = 28;
    const UINT MFD1_BTN6_Id = 29;
    const UINT MFD1_BTN7_Id = 30;
    const UINT MFD1_BTN8_Id = 31;
    const UINT MFD1_BTN9_Id = 32;
    const UINT MFD1_MNU_Id = 33;
    const UINT MFD1_PWR_Id = 34;
    const UINT MFD1_SEL_Id = 35;
    const UINT MFD2_Id = 36;
    const UINT MFD3_Id = 37;
    const UINT MFD4_Id = 38;
    const UINT MFD5_Id = 39;
    const UINT MFD6_Id = 40;
    const UINT Main_windows_Id = 41;
    const UINT Panel_Id = 42;
    const UINT RYoke_Id = 43;
    const UINT RYoke_column_Id = 44;
    const UINT RYoke_column_pedestal_Id = 45;
    const UINT Upper_panel_Id = 46;
    constexpr VECTOR3 Axis_LYoke_column_Location =     {-0.6843, 7.7549, 22.7443};
    constexpr VECTOR3 Axis_RYoke_column_Location =     {0.7956, 7.7505, 22.7433};
    constexpr VECTOR3 Axis_landing_gear_lever_Location =     {0.1746, 8.1530, 22.9745};
    constexpr VECTOR3 PL1_Location =     {-1.0490, 8.6757, 22.2532};
    constexpr VECTOR3 PL2_Location =     {1.2582, 8.6757, 22.2532};
    constexpr VECTOR3 Autopilot_panel_Location =     {0.0519, 8.3417, 22.9115};
    constexpr VECTOR3 Autopilot_screen2_Location =     {-0.0058, 8.3716, 22.8684};
    constexpr VECTOR3 Autopilot_screen3_Location =     {0.1238, 8.3723, 22.8680};
    constexpr VECTOR3 Autopilot_screen4_Location =     {0.2545, 8.3710, 22.8684};
    constexpr VECTOR3 Autopilot_screen1_Location =     {-0.1317, 8.3724, 22.8687};
    constexpr VECTOR3 Captains_camera_Location =     {-0.6788, 8.5281, 22.0996};
    constexpr VECTOR3 Captain_seat_Location =     {-0.6981, 8.1981, 22.0368};
    constexpr VECTOR3 Cockpit_fuselage_Location =     {0.0378, 8.0917, 22.2575};
    constexpr VECTOR3 Upper_panel_Location =     {0.0411, 8.9389, 21.5910};
    constexpr VECTOR3 First_officer_seat_Location =     {0.8019, 8.1981, 22.0368};
    constexpr VECTOR3 LYoke_Location =     {-0.6868, 8.2174, 22.6788};
    constexpr VECTOR3 LYoke_column_Location =     {-0.6846, 8.0161, 22.7373};
    constexpr VECTOR3 LYoke_column_pedestal_Location =     {-0.6846, 7.7376, 22.7435};
    constexpr VECTOR3 Panel_Location =     {0.0371, 8.1096, 23.1863};
    constexpr VECTOR3 RYoke_Location =     {0.7932, 8.2128, 22.6788};
    constexpr VECTOR3 RYoke_column_Location =     {0.7954, 8.0116, 22.7373};
    constexpr VECTOR3 RYoke_column_pedestal_Location =     {0.7954, 7.7330, 22.7435};
    constexpr VECTOR3 Central_pedestal_Location =     {0.0337, 7.8247, 22.2326};
    constexpr VECTOR3 Main_windows_Location =     {0.0411, 8.4046, 22.5669};
    constexpr VECTOR3 MFD1_Location =     {-0.6414, 8.1462, 22.9341};
    constexpr VECTOR3 MFD2_Location =     {-0.4264, 8.1462, 22.9341};
    constexpr VECTOR3 MFD3_Location =     {-0.2015, 8.1559, 22.9387};
    constexpr VECTOR3 MFD4_Location =     {0.0382, 8.1468, 22.9377};
    constexpr VECTOR3 Landing_gear_lever_Location =     {0.1742, 8.0810, 22.9029};
    constexpr VECTOR3 MFD6_Location =     {0.7051, 8.1354, 22.9341};
    constexpr VECTOR3 MFD5_Location =     {0.5004, 8.1462, 22.9341};
    constexpr VECTOR3 Central_pedestal_MFD1_Location =     {0.0328, 8.0019, 22.8584};
    constexpr VECTOR3 Central_pedestal_MFD2_Location =     {0.0331, 7.9435, 22.0611};
    constexpr VECTOR3 Central_pedestal_MFD3_Location =     {0.0445, 8.0056, 22.7361};
    constexpr VECTOR3 Engineer_seat_Location =     {0.2569, 8.1981, 21.2978};
    constexpr VECTOR3 First_officer_camera_Location =     {0.8212, 8.5281, 22.0996};
    constexpr VECTOR3 Engineer_camera_Location =     {0.2981, 8.5281, 21.1919};
    constexpr VECTOR3 MFD1_BTN1_Location =     {-0.7364, 8.2121, 22.9365};
    constexpr VECTOR3 MFD1_BTN2_Location =     {-0.7364, 8.1860, 22.9365};
    constexpr VECTOR3 MFD1_BTN3_Location =     {-0.7364, 8.1600, 22.9365};
    constexpr VECTOR3 MFD1_BTN4_Location =     {-0.7364, 8.1339, 22.9366};
    constexpr VECTOR3 MFD1_BTN5_Location =     {-0.7364, 8.1079, 22.9366};
    constexpr VECTOR3 MFD1_BTN6_Location =     {-0.7363, 8.0818, 22.9367};
    constexpr VECTOR3 MFD1_BTN7_Location =     {-0.5457, 8.2147, 22.9364};
    constexpr VECTOR3 MFD1_BTN8_Location =     {-0.5457, 8.1873, 22.9365};
    constexpr VECTOR3 MFD1_BTN9_Location =     {-0.5457, 8.1599, 22.9365};
    constexpr VECTOR3 MFD1_BTN10_Location =     {-0.5457, 8.1326, 22.9365};
    constexpr VECTOR3 MFD1_BTN11_Location =     {-0.5457, 8.1052, 22.9366};
    constexpr VECTOR3 MFD1_BTN12_Location =     {-0.5457, 8.0778, 22.9366};
    constexpr VECTOR3 MFD1_SEL_Location =     {-0.5911, 8.0449, 22.9367};
    constexpr VECTOR3 MFD1_MNU_Location =     {-0.5689, 8.0449, 22.9367};
    constexpr VECTOR3 MFD1_PWR_Location =     {-0.7133, 8.0449, 22.9367};


#endif
