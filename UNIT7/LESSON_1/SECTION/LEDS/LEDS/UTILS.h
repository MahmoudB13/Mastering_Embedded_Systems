/*
 * UTILS.h
 *
 * Created: 14/07/2024 7:15:18 AM
 *  Author: mahmo
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define GET_BIT(reg, bit)		((reg >> bit) & 1)
#define SET_BIT(reg,bit)		reg |=  (1<<bit)
#define CLEAR_BIT(reg,bit)		reg &= ~(1<<bit)
#define TOGGLE_BIT(reg,bit)		reg ^=  (1<<bit)



#endif /* UTILS_H_ */