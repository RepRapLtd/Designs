//
// Default values for generating gcode from a PCB.
//
// These settings were last changed with pcb-gcode-setup: 12/09/2016 12:28
//
//
// Changes you make in this file will be overwritten if you use pcb-gcode-setup.
//

int SINGLE_PASS = NO;
real ISO_MIN = 0.025000;
real ISO_MAX = 0.500000;
real ISO_STEP = 0.080000;

int GENERATE_TOP_OUTLINES = NO;
int GENERATE_TOP_DRILL = NO;
int GENERATE_TOP_FILL = NO;
int GENERATE_TOP_STENCIL = NO;

int GENERATE_BOTTOM_OUTLINES = YES;
int GENERATE_BOTTOM_DRILL = YES;
int GENERATE_BOTTOM_FILL = NO;
int GENERATE_BOTTOM_STENCIL = NO;

int MIRROR_BOTTOM = NO;
int SIMPLE_DRILL_CODE = YES;

int GENERATE_MILLING = NO;
int CLIMB_MILLING = YES;

int GENERATE_TEXT = NO;

int SPOT_DRILL = NO;
real SPOT_DRILL_DEPTH = -2.500000;

int DO_TOOL_CHANGE_WITH_ZERO_STEP = YES;

int FLIP_BOARD_IN_Y = NO;

//int OUTPUT_UNITS = U_MICRONS;
int OUTPUT_UNITS = U_MILLIMETERS;
//int OUTPUT_UNITS = U_MILS;
//int OUTPUT_UNITS = U_INCHES;
string NC_OPERATOR_MESSAGE = "";
int PREVIEW_WINDOW_WIDTH = 800;
int PREVIEW_WINDOW_HEIGHT = 600;
