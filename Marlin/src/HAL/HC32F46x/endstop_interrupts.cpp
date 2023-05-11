#include "endstop_interrupts.h"
#include "../../module/endstops.h"
#include "interrupts.h"

// Z_MIN_PROBE does not follow the same naming as all other pins...
#if HAS_Z_MIN_PIN && !defined(USE_Z_MIN_PROBE)
#define USE_Z_MIN_PROBE
#endif

//
// IRQ handler
//
void endstopIRQHandler()
{
    bool flag = false;

// check all irq flags
#define CHECK(name) TERN_(USE_##name, flag |= checkAndClearExtIRQFlag(name##_PIN))

    CHECK(X_MAX);
    CHECK(X_MIN);

    CHECK(Y_MAX);
    CHECK(Y_MIN);

    CHECK(Z_MAX);
    CHECK(Z_MIN);

    CHECK(Z2_MAX);
    CHECK(Z2_MIN);

    CHECK(Z3_MAX);
    CHECK(Z3_MIN);

    CHECK(Z_MIN_PROBE);

    // update endstops
    if (flag)
    {
        endstops.update();
    }
}

//
// HAL functions
//
void setup_endstop_interrupts()
{
#define SETUP(name) TERN_(USE_##name, attachInterrupt(name##_PIN, endstopIRQHandler, CHANGE))

    SETUP(X_MAX);
    SETUP(X_MIN);

    SETUP(Y_MAX);
    SETUP(Y_MIN);

    SETUP(Z_MAX);
    SETUP(Z_MIN);

    SETUP(Z2_MAX);
    SETUP(Z2_MIN);

    SETUP(Z3_MAX);
    SETUP(Z3_MIN);

    SETUP(Z_MIN_PROBE);
}

// ensure max. 10 irqs are registered
// if you encounter this error, you'll have to disable some endstops
#if USE_X_MAX && USE_X_MIN && USE_Y_MAX && USE_Y_MIN && USE_Z_MAX && USE_Z_MIN && USE_Z2_MAX && USE_Z2_MIN && USE_Z3_MAX && USE_Z3_MIN && USE_MIN_Z_PROBE
#error "too many endstop interrupts! HC32F46x only supports 10 endstop interrupts."
#endif
