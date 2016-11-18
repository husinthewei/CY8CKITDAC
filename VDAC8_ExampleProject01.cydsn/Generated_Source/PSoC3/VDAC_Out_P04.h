/*******************************************************************************
* File Name: VDAC_Out_P04.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_VDAC_Out_P04_H) /* Pins VDAC_Out_P04_H */
#define CY_PINS_VDAC_Out_P04_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VDAC_Out_P04_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VDAC_Out_P04_Write(uint8 value) ;
void    VDAC_Out_P04_SetDriveMode(uint8 mode) ;
uint8   VDAC_Out_P04_ReadDataReg(void) ;
uint8   VDAC_Out_P04_Read(void) ;
void    VDAC_Out_P04_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   VDAC_Out_P04_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VDAC_Out_P04_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define VDAC_Out_P04_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define VDAC_Out_P04_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define VDAC_Out_P04_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define VDAC_Out_P04_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define VDAC_Out_P04_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define VDAC_Out_P04_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define VDAC_Out_P04_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define VDAC_Out_P04_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VDAC_Out_P04_MASK               VDAC_Out_P04__MASK
#define VDAC_Out_P04_SHIFT              VDAC_Out_P04__SHIFT
#define VDAC_Out_P04_WIDTH              1u

/* Interrupt constants */
#if defined(VDAC_Out_P04__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VDAC_Out_P04_SetInterruptMode() function.
     *  @{
     */
        #define VDAC_Out_P04_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define VDAC_Out_P04_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define VDAC_Out_P04_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define VDAC_Out_P04_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define VDAC_Out_P04_INTR_MASK      (0x01u)
#endif /* (VDAC_Out_P04__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VDAC_Out_P04_PS                     (* (reg8 *) VDAC_Out_P04__PS)
/* Data Register */
#define VDAC_Out_P04_DR                     (* (reg8 *) VDAC_Out_P04__DR)
/* Port Number */
#define VDAC_Out_P04_PRT_NUM                (* (reg8 *) VDAC_Out_P04__PRT) 
/* Connect to Analog Globals */                                                  
#define VDAC_Out_P04_AG                     (* (reg8 *) VDAC_Out_P04__AG)                       
/* Analog MUX bux enable */
#define VDAC_Out_P04_AMUX                   (* (reg8 *) VDAC_Out_P04__AMUX) 
/* Bidirectional Enable */                                                        
#define VDAC_Out_P04_BIE                    (* (reg8 *) VDAC_Out_P04__BIE)
/* Bit-mask for Aliased Register Access */
#define VDAC_Out_P04_BIT_MASK               (* (reg8 *) VDAC_Out_P04__BIT_MASK)
/* Bypass Enable */
#define VDAC_Out_P04_BYP                    (* (reg8 *) VDAC_Out_P04__BYP)
/* Port wide control signals */                                                   
#define VDAC_Out_P04_CTL                    (* (reg8 *) VDAC_Out_P04__CTL)
/* Drive Modes */
#define VDAC_Out_P04_DM0                    (* (reg8 *) VDAC_Out_P04__DM0) 
#define VDAC_Out_P04_DM1                    (* (reg8 *) VDAC_Out_P04__DM1)
#define VDAC_Out_P04_DM2                    (* (reg8 *) VDAC_Out_P04__DM2) 
/* Input Buffer Disable Override */
#define VDAC_Out_P04_INP_DIS                (* (reg8 *) VDAC_Out_P04__INP_DIS)
/* LCD Common or Segment Drive */
#define VDAC_Out_P04_LCD_COM_SEG            (* (reg8 *) VDAC_Out_P04__LCD_COM_SEG)
/* Enable Segment LCD */
#define VDAC_Out_P04_LCD_EN                 (* (reg8 *) VDAC_Out_P04__LCD_EN)
/* Slew Rate Control */
#define VDAC_Out_P04_SLW                    (* (reg8 *) VDAC_Out_P04__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VDAC_Out_P04_PRTDSI__CAPS_SEL       (* (reg8 *) VDAC_Out_P04__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VDAC_Out_P04_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VDAC_Out_P04__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VDAC_Out_P04_PRTDSI__OE_SEL0        (* (reg8 *) VDAC_Out_P04__PRTDSI__OE_SEL0) 
#define VDAC_Out_P04_PRTDSI__OE_SEL1        (* (reg8 *) VDAC_Out_P04__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VDAC_Out_P04_PRTDSI__OUT_SEL0       (* (reg8 *) VDAC_Out_P04__PRTDSI__OUT_SEL0) 
#define VDAC_Out_P04_PRTDSI__OUT_SEL1       (* (reg8 *) VDAC_Out_P04__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VDAC_Out_P04_PRTDSI__SYNC_OUT       (* (reg8 *) VDAC_Out_P04__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VDAC_Out_P04__SIO_CFG)
    #define VDAC_Out_P04_SIO_HYST_EN        (* (reg8 *) VDAC_Out_P04__SIO_HYST_EN)
    #define VDAC_Out_P04_SIO_REG_HIFREQ     (* (reg8 *) VDAC_Out_P04__SIO_REG_HIFREQ)
    #define VDAC_Out_P04_SIO_CFG            (* (reg8 *) VDAC_Out_P04__SIO_CFG)
    #define VDAC_Out_P04_SIO_DIFF           (* (reg8 *) VDAC_Out_P04__SIO_DIFF)
#endif /* (VDAC_Out_P04__SIO_CFG) */

/* Interrupt Registers */
#if defined(VDAC_Out_P04__INTSTAT)
    #define VDAC_Out_P04_INTSTAT             (* (reg8 *) VDAC_Out_P04__INTSTAT)
    #define VDAC_Out_P04_SNAP                (* (reg8 *) VDAC_Out_P04__SNAP)
    
	#define VDAC_Out_P04_0_INTTYPE_REG 		(* (reg8 *) VDAC_Out_P04__0__INTTYPE)
#endif /* (VDAC_Out_P04__INTSTAT) */

#endif /* End Pins VDAC_Out_P04_H */


/* [] END OF FILE */
