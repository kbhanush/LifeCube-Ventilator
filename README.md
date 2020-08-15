# LifeCube-Ventilator
Open Source Oxygenator and Ventilator

The LifeCube oxygenator and  ventilator is an emergency use respiratory device that can be assembled by anyone with basic computer hardware and software skills. It is designed to assist people with respiratory illnesses to breathe better. It can function as a CPAP in O2 mode by pumping air/O2 in a hyperbaric hood/chamber. In the ventilator mode it can function as a volume/pressure ventilator in controlled mode only i.e. the breathing cycles, once configured, are ventilator induced. Patient cannot initiate a breathing cycle.  It can be configured to deliver a preset pressure cycle, preset volume and respiration rate. A PEEP control valve placed on the resuscitator bag (aka ambu bag) can be used to retain the required Positive Expiratory Pressure. Some resuscitator bags also include an inlet tube for supplementary oxygen or nebulization and are recommended to aid in sufficient oxygenation of patients

Device operates on regular AC power 110 / 220V 3-Pin outlets.

All ventilator parameters can be controlled via a mobile app that can be connected to the device over bluetooth. WiFi is not required to operate the device. The idea is to put the controls in the hands of the patient since breathing generally varies and patient can tweak the breathing cycle per their comfort. Absense of physical controls on the device also make it tamper proof or erroneous changes. Note that the initial setup of pressure and volume should be done by a physician or in consultation with one. Incorrect pressure and volume setting can cause irrervisble lung damage!


The .svg files in this repository were used to Laser cut all parts used to build the ventilator. You may use these to laser cut or handcut each piece using 1/4" think acrylic or 1/2" thick plywood.

The power supply unit used in ventilator can be built from desktop computer PSU which has ample 12V and 5V DC supply lines. Simply remove the main board and fan from any PSU. Some PSUs reqiure pin 14 on the ATX molex connector to be grounded. There are plenty of articles on the web on converting an ATX power supply to a bench power supply. I then used some buck converters to regulate the supply.

The microcontroller used in the ventilator is an Arduino Uno. Arduino controls the 2 servo motors that drive the compression arms. Arduino code is included in the repo

Servo motors used are Annimos DC Servo motors producing max torque of 85 Kg-cm. A higher torque servo is advisable if you can find one that operates under 12V DC. 

Bluetooth module used is DSD-Tech HC-05 which works with Andriod only. I am trying other modules that support both Android & iOS but they have some issues. 

Mobile app is built using the Ionic framework and therefore a single codebase can be used to generate compiled binaries for both Andriod and iOS. App is currently available in the andriod store.

You may also need a pressure guage for calibration since that would vary with the type of bag used. I used a simple hand-held pressure guage I ordered from Amazon for $30.


