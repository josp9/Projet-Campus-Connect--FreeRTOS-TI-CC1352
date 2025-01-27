/*
 *  ======== syscfg_c.rov.xs ========
 *  This file contains the information needed by the Runtime Object
 *  View (ROV) tool.
 *
 *  Specifically, this file names the C-ROV implementation files declared
 *  by the modules that are part of the app's configuration.  In the
 *  future this file will also contain a serialization of corresponding
 *  module configuration parameters which can be used by the ROV provided
 *  views.
 *
 *  DO NOT EDIT - This file is generated by the SysConfig tool.
 */
var crovFiles = [
    "kernel/freertos/rov/heap.rov.js", /* /freertos/FreeRTOS ROV support */
    "kernel/freertos/rov/helper.rov.js", /* /freertos/FreeRTOS ROV support */
    "kernel/freertos/rov/mutex.rov.js", /* /freertos/FreeRTOS ROV support */
    "kernel/freertos/rov/queue.rov.js", /* /freertos/FreeRTOS ROV support */
    "kernel/freertos/rov/semaphore.rov.js", /* /freertos/FreeRTOS ROV support */
    "kernel/freertos/rov/stack.rov.js", /* /freertos/FreeRTOS ROV support */
    "kernel/freertos/rov/task.rov.js", /* /freertos/FreeRTOS ROV support */
    "kernel/freertos/rov/timer.rov.js", /* /freertos/FreeRTOS ROV support */
    "kernel/freertos/rov/clock.rov.js", /* /freertos/dpl/Settings ROV support */
    "kernel/freertos/rov/exception.rov.js", /* /freertos/dpl/Settings ROV support */
    "kernel/freertos/rov/hwi.rov.js", /* /freertos/dpl/Settings ROV support */
    "kernel/freertos/rov/nvic.rov.js", /* /freertos/dpl/Settings ROV support */
];
