#undef MASTER_RIGHT
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS

#define MATRIX_ROW_PINS { B4, B2, B5, B6 }
// #define MATRIX_COL_PINS { B1, D7, F7, C6, F6, D4 }
#define MATRIX_COL_PINS { D4, F6, C6, F7, D7, B1 }

#ifdef RGB_DI_PIN
  //#define RGBLIGHT_SPLIT
  #undef RGBLED_NUM
  #define RGBLED_NUM 44
#endif
