#pragma once
/* From glfw3.h */

/* The unknown key */
#define JOLT_KEY_UNKNOWN            -1

/* Printable keys */
#define JOLT_KEY_SPACE              32
#define JOLT_KEY_APOSTROPHE         39  /* ' */
#define JOLT_KEY_COMMA              44  /* , */
#define JOLT_KEY_MINUS              45  /* - */
#define JOLT_KEY_PERIOD             46  /* . */
#define JOLT_KEY_SLASH              47  /* / */
#define JOLT_KEY_0                  48
#define JOLT_KEY_1                  49
#define JOLT_KEY_2                  50
#define JOLT_KEY_3                  51
#define JOLT_KEY_4                  52
#define JOLT_KEY_5                  53
#define JOLT_KEY_6                  54
#define JOLT_KEY_7                  55
#define JOLT_KEY_8                  56
#define JOLT_KEY_9                  57
#define JOLT_KEY_SEMICOLON          59  /* ; */
#define JOLT_KEY_EQUAL              61  /* = */
#define JOLT_KEY_A                  65
#define JOLT_KEY_B                  66
#define JOLT_KEY_C                  67
#define JOLT_KEY_D                  68
#define JOLT_KEY_E                  69
#define JOLT_KEY_F                  70
#define JOLT_KEY_G                  71
#define JOLT_KEY_H                  72
#define JOLT_KEY_I                  73
#define JOLT_KEY_J                  74
#define JOLT_KEY_K                  75
#define JOLT_KEY_L                  76
#define JOLT_KEY_M                  77
#define JOLT_KEY_N                  78
#define JOLT_KEY_O                  79
#define JOLT_KEY_P                  80
#define JOLT_KEY_Q                  81
#define JOLT_KEY_R                  82
#define JOLT_KEY_S                  83
#define JOLT_KEY_T                  84
#define JOLT_KEY_U                  85
#define JOLT_KEY_V                  86
#define JOLT_KEY_W                  87
#define JOLT_KEY_X                  88
#define JOLT_KEY_Y                  89
#define JOLT_KEY_Z                  90
#define JOLT_KEY_LEFT_BRACKET       91  /* [ */
#define JOLT_KEY_BACKSLASH          92  /* \ */
#define JOLT_KEY_RIGHT_BRACKET      93  /* ] */
#define JOLT_KEY_GRAVE_ACCENT       96  /* ` */
#define JOLT_KEY_WORLD_1            161 /* non-US #1 */
#define JOLT_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define JOLT_KEY_ESCAPE             256
#define JOLT_KEY_ENTER              257
#define JOLT_KEY_TAB                258
#define JOLT_KEY_BACKSPACE          259
#define JOLT_KEY_INSERT             260
#define JOLT_KEY_DELETE             261
#define JOLT_KEY_RIGHT              262
#define JOLT_KEY_LEFT               263
#define JOLT_KEY_DOWN               264
#define JOLT_KEY_UP                 265
#define JOLT_KEY_PAGE_UP            266
#define JOLT_KEY_PAGE_DOWN          267
#define JOLT_KEY_HOME               268
#define JOLT_KEY_END                269
#define JOLT_KEY_CAPS_LOCK          280
#define JOLT_KEY_SCROLL_LOCK        281
#define JOLT_KEY_NUM_LOCK           282
#define JOLT_KEY_PRINT_SCREEN       283
#define JOLT_KEY_PAUSE              284
#define JOLT_KEY_F1                 290
#define JOLT_KEY_F2                 291
#define JOLT_KEY_F3                 292
#define JOLT_KEY_F4                 293
#define JOLT_KEY_F5                 294
#define JOLT_KEY_F6                 295
#define JOLT_KEY_F7                 296
#define JOLT_KEY_F8                 297
#define JOLT_KEY_F9                 298
#define JOLT_KEY_F10                299
#define JOLT_KEY_F11                300
#define JOLT_KEY_F12                301
#define JOLT_KEY_F13                302
#define JOLT_KEY_F14                303
#define JOLT_KEY_F15                304
#define JOLT_KEY_F16                305
#define JOLT_KEY_F17                306
#define JOLT_KEY_F18                307
#define JOLT_KEY_F19                308
#define JOLT_KEY_F20                309
#define JOLT_KEY_F21                310
#define JOLT_KEY_F22                311
#define JOLT_KEY_F23                312
#define JOLT_KEY_F24                313
#define JOLT_KEY_F25                314
#define JOLT_KEY_KP_0               320
#define JOLT_KEY_KP_1               321
#define JOLT_KEY_KP_2               322
#define JOLT_KEY_KP_3               323
#define JOLT_KEY_KP_4               324
#define JOLT_KEY_KP_5               325
#define JOLT_KEY_KP_6               326
#define JOLT_KEY_KP_7               327
#define JOLT_KEY_KP_8               328
#define JOLT_KEY_KP_9               329
#define JOLT_KEY_KP_DECIMAL         330
#define JOLT_KEY_KP_DIVIDE          331
#define JOLT_KEY_KP_MULTIPLY        332
#define JOLT_KEY_KP_SUBTRACT        333
#define JOLT_KEY_KP_ADD             334
#define JOLT_KEY_KP_ENTER           335
#define JOLT_KEY_KP_EQUAL           336
#define JOLT_KEY_LEFT_SHIFT         340
#define JOLT_KEY_LEFT_CONTROL       341
#define JOLT_KEY_LEFT_ALT           342
#define JOLT_KEY_LEFT_SUPER         343
#define JOLT_KEY_RIGHT_SHIFT        344
#define JOLT_KEY_RIGHT_CONTROL      345
#define JOLT_KEY_RIGHT_ALT          346
#define JOLT_KEY_RIGHT_SUPER        347
#define JOLT_KEY_MENU               348

#define JOLT_KEY_LAST               JOLT_KEY_MENU

/* Mouse Buttons */
#define JOLT_MOUSE_BUTTON_1         0
#define JOLT_MOUSE_BUTTON_2         1
#define JOLT_MOUSE_BUTTON_3         2
#define JOLT_MOUSE_BUTTON_4         3
#define JOLT_MOUSE_BUTTON_5         4
#define JOLT_MOUSE_BUTTON_6         5
#define JOLT_MOUSE_BUTTON_7         6
#define JOLT_MOUSE_BUTTON_8         7
#define JOLT_MOUSE_BUTTON_LAST      JOLT_MOUSE_BUTTON_8
#define JOLT_MOUSE_BUTTON_LEFT      JOLT_MOUSE_BUTTON_1
#define JOLT_MOUSE_BUTTON_RIGHT     JOLT_MOUSE_BUTTON_2
#define JOLT_MOUSE_BUTTON_MIDDLE    JOLT_MOUSE_BUTTON_3