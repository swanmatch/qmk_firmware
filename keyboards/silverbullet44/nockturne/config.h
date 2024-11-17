// #undef MASTER_RIGHT
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

#define MATRIX_ROW_PINS { B4, B2, B5, B6 }
// #define MATRIX_COL_PINS { B1, D7, F7, C6, F6, D4 }
#define MATRIX_COL_PINS { D4, F6, C6, F7, D7, B1 }
// #define SELECT_SOFT_SERIAL_SPEED 0
// #undef MASTER_RIGHT

// #define SPLIT_POINTING_ENABLE
// #define POINTING_DEVICE_COMBINED
// #define ENCODERS_PAD_A {E6}
// #define ENCODERS_PAD_B {B3}
#define ENCODERS_PAD_A { E6 }
#define ENCODERS_PAD_B { B3 }
#define ENCODERS_RESOLUTIONS { 4 }

#ifdef RGB_DI_PIN
  #undef RGBLED_NUM
  #undef RGBLED_SPLIT
  #undef RGBLIGHT_LED_MAP
  #define RGBLED_NUM 44
  #define RGBLED_SPLIT {22, 22}
#endif
