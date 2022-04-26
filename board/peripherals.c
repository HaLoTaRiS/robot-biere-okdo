/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v11.0
processor: LPC55S69
package_id: LPC55S69JBD100
mcu_data: ksdk2_0
processor_version: 11.0.1
board: LPCXpresso55S69
functionalGroups:
- name: BOARD_InitPeripherals_cm33_core0
  UUID: 61d0725d-b300-49cb-9c66-b5edfbf8ffc1
  called_from_default_init: true
  selectedCore: cm33_core0
- name: BOARD_InitPeripherals_cm33_core1
  UUID: e2041cd4-ebb6-45a5-807f-e0c2dc047d48
  selectedCore: cm33_core1
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals_cm33_core0 functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * NVIC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
- functional_group: 'BOARD_InitPeripherals_cm33_core0'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * GINT0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GINT0'
- type: 'gint'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'gint_f9751e057606760f4d52cb811c360fa8'
- functional_group: 'BOARD_InitPeripherals_cm33_core0'
- peripheral: 'GINT0'
- config_sets:
  - fsl_gint:
    - commonCfg:
      - gint_comb: 'kGINT_CombineOr'
      - gint_trig: 'kGINT_TrigEdge'
    - callbackCfg:
      - callback_name: 'gint0_callback'
      - isCallbackEnabled: 'true'
      - enable_priority: 'false'
    - pins_port0:
      - enable:
        - enable_low:
          - 0: 'no'
          - 1: 'no'
          - 2: 'no'
          - 3: 'no'
          - 4: 'no'
          - 5: 'no'
          - 6: 'no'
          - 7: 'no'
          - 8: 'no'
          - 9: 'no'
          - 10: 'no'
          - 11: 'no'
          - 12: 'no'
          - 13: 'no'
          - 14: 'no'
          - 15: 'no'
        - enable_high:
          - 0: 'no'
          - 1: 'no'
          - 2: 'no'
          - 3: 'no'
          - 4: 'no'
          - 5: 'no'
          - 6: 'no'
          - 7: 'no'
          - 8: 'no'
          - 9: 'no'
          - 10: 'no'
          - 11: 'no'
          - 12: 'no'
          - 13: 'no'
          - 14: 'no'
          - 15: 'no'
      - polarity:
        - polarity_low:
          - 0: 'low'
          - 1: 'low'
          - 2: 'low'
          - 3: 'low'
          - 4: 'low'
          - 5: 'low'
          - 6: 'low'
          - 7: 'low'
          - 8: 'low'
          - 9: 'low'
          - 10: 'low'
          - 11: 'low'
          - 12: 'low'
          - 13: 'low'
          - 14: 'low'
          - 15: 'low'
        - polarity_high:
          - 0: 'low'
          - 1: 'low'
          - 2: 'low'
          - 3: 'low'
          - 4: 'low'
          - 5: 'low'
          - 6: 'low'
          - 7: 'low'
          - 8: 'low'
          - 9: 'low'
          - 10: 'low'
          - 11: 'low'
          - 12: 'low'
          - 13: 'low'
          - 14: 'low'
          - 15: 'low'
    - pins_port1:
      - enable:
        - enable_low:
          - 0: 'no'
          - 1: 'no'
          - 2: 'no'
          - 3: 'no'
          - 4: 'no'
          - 5: 'no'
          - 6: 'no'
          - 7: 'no'
          - 8: 'no'
          - 9: 'no'
          - 10: 'no'
          - 11: 'no'
          - 12: 'no'
          - 13: 'no'
          - 14: 'no'
          - 15: 'no'
        - enable_high:
          - 0: 'no'
          - 1: 'no'
          - 2: 'no'
          - 3: 'no'
          - 4: 'no'
          - 5: 'no'
          - 6: 'no'
          - 7: 'no'
          - 8: 'no'
          - 9: 'no'
          - 10: 'no'
          - 11: 'no'
          - 12: 'no'
          - 13: 'no'
          - 14: 'no'
          - 15: 'no'
      - polarity:
        - polarity_low:
          - 0: 'low'
          - 1: 'low'
          - 2: 'low'
          - 3: 'low'
          - 4: 'low'
          - 5: 'low'
          - 6: 'low'
          - 7: 'low'
          - 8: 'low'
          - 9: 'low'
          - 10: 'low'
          - 11: 'low'
          - 12: 'low'
          - 13: 'low'
          - 14: 'low'
          - 15: 'low'
        - polarity_high:
          - 0: 'low'
          - 1: 'low'
          - 2: 'low'
          - 3: 'low'
          - 4: 'low'
          - 5: 'low'
          - 6: 'low'
          - 7: 'low'
          - 8: 'low'
          - 9: 'low'
          - 10: 'low'
          - 11: 'low'
          - 12: 'low'
          - 13: 'low'
          - 14: 'low'
          - 15: 'low'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

static void GINT0_init(void) {
  /* Set GINT control registers and the name of callback function */
  GINT_SetCtrl(GINT0_PERIPHERAL, kGINT_CombineOr, kGINT_TrigEdge, gint0_callback);
  /* Select pins and polarity for GINT - PIO0 */
  GINT_ConfigPins(GINT0_PERIPHERAL, kGINT_Port0, GINT0_PIO0_POLARITY_MASK, GINT0_PIO0_ENABLED_PINS_MASK);
  /* Select pins and polarity for GINT - PIO1 */
  GINT_ConfigPins(GINT0_PERIPHERAL, kGINT_Port1, GINT0_PIO1_POLARITY_MASK, GINT0_PIO1_ENABLED_PINS_MASK);
  /* Enable callback for GINT */
  GINT_EnableCallback(GINT0_PERIPHERAL);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals_cm33_core0(void)
{
  /* Global initialization */
  /* GINT initialization */
  GINT_Init(GINT0_PERIPHERAL);

  /* Initialize components */
  GINT0_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals_cm33_core0();
}
