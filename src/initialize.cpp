#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
 static  lv_res_t btn_rel_action(lv_obj_t * btn)
 {
     /*Increase the button width*/
     lv_coord_t width = lv_obj_get_width(btn);
     lv_obj_set_width(btn, width + 20);
     lv_obj_set_width(btn, width - 20);
     return LV_RES_OK;
 }

void initialize() {
  pros::lcd::initialize();
  inert.reset();
  // pros::delay(2200);
  rEnc.reset();
  lEnc.reset();


//Help

}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() {

}
