/**
* @file my_state_machine.c
 */

 #include <zephyr/smf.h>
 #include "LED.h"
 #include "my_state_machine.h"
 #include "BTN.h"

 //FUNCTION PROTOTYPES, telling us functions exist and what arguments they accept
//void *o is a generic pointer holding the address of an object of any data type
 static void led_on_state_entry(void* o);
 // enum smf_state_result is the entire type of the function which returns an enumerator 
 //either SMF_EVENT_HANDLED or SMF_EVENT_PROPOGATED
 static enum smf_state_result led_on_state_run(void* o);
 static void led_off_state_entry(void* o);
 static enum smf_state_result led_off_state_run(void* o);

// TYPE DEFS - defining data types our state machine uses

enum led_state_machine_states {
    LED_ON_STATE,
    LED_OFF_STATE
};

typedef struct {
    //Context variable used by zephyr to track state machine state, must be first
    struct smf_ctx ctx;

    uint32_t events; //event based now not count based
} led_state_object_t;

//LOCAL VARIABLES

static const struct smf_state led_states[] = {
    [LED_ON_STATE] = SMF_CREATE_STATE(led_on_state_entry, led_on_state_run, NULL, NULL, NULL),
    [LED_OFF_STATE] = SMF_CREATE_STATE(led_off_state_entry, led_off_state_run, NULL, NULL, NULL)
};

static led_state_object_t led_state_object;

 void state_machine_init(){
    led_state_object.events = 0;
    smf_set_initial(SMF_CTX(&led_state_object), &led_states[LED_ON_STATE]);
 }

 int state_machine_run(){
    led_state_object.events = k_event_wait_safe(&btn_event, BTN_ANY_EVENT, false, K_FOREVER); //waits for button events to be triggered , returns that events have occured, writing to the event variable
    return smf_run_state(SMF_CTX(&led_state_object));
 }

 static void led_on_state_entry(void* o) {
    LED_set(LED0, LED_ON);
 }

 static enum smf_state_result led_on_state_run(void* o) {
    if (led_state_object.events & BTN0_EVENT) {
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_OFF_STATE]);
    } 

    return SMF_EVENT_HANDLED;
 }

 static void led_off_state_entry(void* o) {
    LED_set(LED0, LED_ON);
 }

 static enum smf_state_result led_off_state_run(void* o) {
    if (led_state_object.events & BTN1_EVENT) {
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_ON_STATE]);
    }
    return SMF_EVENT_HANDLED;
 }